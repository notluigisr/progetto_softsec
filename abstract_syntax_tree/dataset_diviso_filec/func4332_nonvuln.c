Item_sum_hybrid::val_str(String *str)
{
  DBUG_ASSERT(fixed == 1);
  if (null_value)
    return 0;
  String *retval= value->val_str(str);
  if ((null_value= value->null_value))
    DBUG_ASSERT(retval == NULL);
  return retval;
}