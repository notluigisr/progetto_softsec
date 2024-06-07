bool Item_sum_max::add()
{
  
  arg_cache->cache_value();
  if (!arg_cache->null_value &&
      (null_value || cmp->compare() > 0))
  {
    value->store(arg_cache);
    value->cache_value();
    null_value= 0;
  }
  return 0;
}