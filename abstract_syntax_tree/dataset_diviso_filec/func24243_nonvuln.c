my_decimal *Item_in_subselect::val_decimal(my_decimal *decimal_value)
{
  
  DBUG_ASSERT(0);
  if (forced_const)
    goto value_is_ready;
  DBUG_ASSERT((engine->uncacheable() & ~UNCACHEABLE_EXPLAIN) ||
              ! engine->is_executed());
  null_value= was_null= FALSE;
  DBUG_ASSERT(fixed == 1);
  if (exec())
  {
    reset();
    return 0;
  }
  if (was_null && !value)
    null_value= TRUE;
value_is_ready:
  int2my_decimal(E_DEC_FATAL_ERROR, value, 0, decimal_value);
  return decimal_value;
}