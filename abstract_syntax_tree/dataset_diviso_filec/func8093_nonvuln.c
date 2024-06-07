Item_param::set_value(THD *thd, sp_rcontext *ctx, Item **it)
{
  Item *arg= *it;
  struct st_value tmp;
  
  if (arg->save_in_value(&tmp) ||
      set_value(thd, arg, &tmp, arg->type_handler()))
  {
    set_null();
    return false;
  }
  
  DBUG_ASSERT(null_value == false);
  return false;
}