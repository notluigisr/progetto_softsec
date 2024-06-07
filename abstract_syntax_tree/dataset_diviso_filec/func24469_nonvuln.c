longlong Item_func_bit_xor::val_int()
{
  DBUG_ASSERT(fixed == 1);
  ulonglong arg1= (ulonglong) args[0]->val_int();
  ulonglong arg2= (ulonglong) args[1]->val_int();
  if ((null_value= (args[0]->null_value || args[1]->null_value)))
    return 0;
  return (longlong) (arg1 ^ arg2);
}