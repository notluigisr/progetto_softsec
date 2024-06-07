parse_iso_time(const char *cp, time_t *t)
{
  struct tm st_tm;
  unsigned int year=0, month=0, day=0, hour=0, minute=0, second=0;
  if (tor_sscanf(cp, "STR", &year, &month,
                &day, &hour, &minute, &second) < 6) {
    char *esc = esc_for_log(cp);
    log_warn(LD_GENERAL, "STR", esc);
    tor_free(esc);
    return -1;
  }
  if (year < 1970 || month < 1 || month > 12 || day < 1 || day > 31 ||
          hour > 23 || minute > 59 || second > 60) {
    char *esc = esc_for_log(cp);
    log_warn(LD_GENERAL, "STR", esc);
    tor_free(esc);
    return -1;
  }
  st_tm.tm_year = year-1900;
  st_tm.tm_mon = month-1;
  st_tm.tm_mday = day;
  st_tm.tm_hour = hour;
  st_tm.tm_min = minute;
  st_tm.tm_sec = second;

  if (st_tm.tm_year < 70) {
    char *esc = esc_for_log(cp);
    log_warn(LD_GENERAL, "STR", esc);
    tor_free(esc);
    return -1;
  }
  *t = tor_timegm(&st_tm);
  return 0;
}