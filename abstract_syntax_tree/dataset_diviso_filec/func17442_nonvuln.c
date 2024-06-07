int Field_timestamp::store(longlong nr, bool unsigned_val)
{
  MYSQL_TIME l_time;
  int error;
  ErrConvInteger str(nr, unsigned_val);
  THD *thd= get_thd();

  longlong tmp= number_to_datetime(nr, 0, &l_time, sql_mode_for_timestamp(thd),
                                   &error);
  return store_TIME_with_warning(thd, &l_time, &str, error, tmp != -1);
}