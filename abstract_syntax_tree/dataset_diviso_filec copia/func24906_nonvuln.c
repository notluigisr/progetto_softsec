format_local_iso_time(char *buf, time_t t)
{
  struct tm tm;
  strftime(buf, ISO_TIME_LEN+1, "STR", tor_localtime_r(&t, &tm));
}