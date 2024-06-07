bool Field_timestamp::get_date(MYSQL_TIME *ltime, ulonglong fuzzydate)
{
  ulong sec_part;
  my_time_t ts= get_timestamp(&sec_part);
  return timestamp_to_TIME(get_thd(), ltime, ts, sec_part, fuzzydate);
}