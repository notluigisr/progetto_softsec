int subselect_uniquesubquery_engine::exec()
{
  DBUG_ENTER("STR");
  int error;
  TABLE *table= tab->table;
  empty_result_set= TRUE;
  table->status= 0;
  Item_in_subselect *in_subs= (Item_in_subselect *) item;

  if (!tab->preread_init_done && tab->preread_init())
    DBUG_RETURN(1);
 
  if (in_subs->left_expr_has_null())
  {
    
    if (in_subs->is_top_level_item())
      DBUG_RETURN(1); 
    else
      DBUG_RETURN(scan_table());
  }

  if (copy_ref_key(true))
  {
    
    in_subs->value= 0;
    DBUG_RETURN(0);
  }

  if (!table->file->inited &&
      (error= table->file->ha_index_init(tab->ref.key, 0)))
  {
    (void) report_error(table, error);
    DBUG_RETURN(true);
  }

  error= table->file->ha_index_read_map(table->record[0],
                                        tab->ref.key_buff,
                                        make_prev_keypart_map(tab->
                                                              ref.key_parts),
                                        HA_READ_KEY_EXACT);
  if (error &&
      error != HA_ERR_KEY_NOT_FOUND && error != HA_ERR_END_OF_FILE)
    error= report_error(table, error);
  else
  {
    error= 0;
    table->null_row= 0;
    if (!table->status && (!cond || cond->val_int()))
    {
      ((Item_in_subselect *) item)->value= 1;
      empty_result_set= FALSE;
    }
    else
      ((Item_in_subselect *) item)->value= 0;
  }

  DBUG_RETURN(error != 0);
}