int Field_timestamp::set_time()
{
  set_notnull();
  store_TIME(get_thd()->query_start(), 0);
  return 0;
}