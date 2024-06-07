bool Item_sum_or::add()
{
  ulonglong value= (ulonglong) args[0]->val_int();
  if (!args[0]->null_value)
  {
    if (as_window_function)
      return add_as_window(value);
    bits|=value;
  }
  return 0;
}