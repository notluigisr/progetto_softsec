int Field_timestamp::store(const char *from,uint len,CHARSET_INFO *cs)
{
  MYSQL_TIME l_time;
  MYSQL_TIME_STATUS status;
  bool have_smth_to_conv;
  ErrConvString str(from, len, cs);
  THD *thd= get_thd();

  
  have_smth_to_conv= !str_to_datetime(cs, from, len, &l_time,
                                      (thd->variables.sql_mode &
                                       MODE_NO_ZERO_DATE) |
                                       MODE_NO_ZERO_IN_DATE, &status);
  return store_TIME_with_warning(thd, &l_time, &str,
                                 status.warnings, have_smth_to_conv);
}