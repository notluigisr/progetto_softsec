int Field_timestamp::store(const char *from,size_t len,CHARSET_INFO *cs)
{
  MYSQL_TIME l_time;
  MYSQL_TIME_STATUS status;
  bool have_smth_to_conv;
  ErrConvString str(from, len, cs);
  THD *thd= get_thd();

  have_smth_to_conv= !str_to_datetime(cs, from, len, &l_time,
                                      sql_mode_for_timestamp(thd), &status);
  return store_TIME_with_warning(thd, &l_time, &str,
                                 status.warnings, have_smth_to_conv);
}