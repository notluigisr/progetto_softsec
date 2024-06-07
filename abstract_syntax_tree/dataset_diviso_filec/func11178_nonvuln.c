bool Item_cache_str::cache_value()
{
  if (!example)
  {
    DBUG_ASSERT(value_cached == FALSE);
    return FALSE;
  }
  value_cached= TRUE;
  value_buff.set(buffer, sizeof(buffer), example->collation.collation);
  value= example->str_result(&value_buff);
  if ((null_value= null_value_inside= example->null_value))
    value= 0;
  else if (value != &value_buff)
  {
    
    value_buff.copy(*value);
    value= &value_buff;
  }
  else
    value_buff.copy();
  return TRUE;
}