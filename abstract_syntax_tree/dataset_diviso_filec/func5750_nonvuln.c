Item_func::eval_not_null_tables(void *opt_arg)
{
  Item **arg,**arg_end;
  not_null_tables_cache= 0;
  if (arg_count)
  {		
    for (arg=args, arg_end=args+arg_count; arg != arg_end ; arg++)
    {
      not_null_tables_cache|= (*arg)->not_null_tables();
    }
  }
  return FALSE;
}