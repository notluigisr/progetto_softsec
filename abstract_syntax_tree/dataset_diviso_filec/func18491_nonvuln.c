bool Item_func_group_concat::add()
{
  if (always_null)
    return 0;
  copy_fields(tmp_table_param);
  if (copy_funcs(tmp_table_param->items_to_copy, table->in_use))
    return TRUE;

  size_t row_str_len= 0;
  StringBuffer<MAX_FIELD_WIDTH> buf;
  String *res;
  for (uint i= 0; i < arg_count_field; i++)
  {
    Item *show_item= args[i];
    if (show_item->const_item())
      continue;

    Field *field= show_item->get_tmp_table_field();
    if (field)
    {
      if (field->is_null_in_record((const uchar*) table->record[0]))
        return 0;                    
      if (tree && (res= field->val_str(&buf)))
        row_str_len+= res->length();
    }
  }

  null_value= FALSE;
  bool row_eligible= TRUE;

  if (distinct) 
  {
    
    uint count= unique_filter->elements_in_tree();
    unique_filter->unique_add(table->record[0] + table->s->null_bytes);
    if (count == unique_filter->elements_in_tree())
      row_eligible= FALSE;
  }

  TREE_ELEMENT *el= 0;                          
  if (row_eligible && tree)
  {
    THD *thd= table->in_use;
    table->field[0]->store(row_str_len, FALSE);
    if ((tree_len >> GCONCAT_REPACK_FACTOR) > thd->variables.group_concat_max_len
        && tree->elements_in_tree > 1)
      if (repack_tree(thd))
        return 1;
    el= tree_insert(tree, table->record[0] + table->s->null_bytes, 0,
                    tree->custom_arg);
    
    if (!el)
      return 1;
    tree_len+= row_str_len;
  }
  
  if (row_eligible && !warning_for_row &&
      (!tree || (el->count == 1 && distinct && !arg_count_order)))
    dump_leaf_key(table->record[0] + table->s->null_bytes, 1, this);

  return 0;
}