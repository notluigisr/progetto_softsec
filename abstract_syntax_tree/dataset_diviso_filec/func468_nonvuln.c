bool Item_func_set_user_var::register_field_in_read_map(void *arg)
{
  if (result_field)
  {
    TABLE *table= (TABLE *) arg;
    if (result_field->table == table || !table)
      bitmap_set_bit(result_field->table->read_set, result_field->field_index);
    if (result_field->vcol_info)
      return result_field->vcol_info->
               expr->walk(&Item::register_field_in_read_map, 1, arg);
  }
  return 0;
}