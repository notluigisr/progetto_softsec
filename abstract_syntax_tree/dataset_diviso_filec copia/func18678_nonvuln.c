static void debug_printf(u_int32_t protocol, void *id_struct,
			 ndpi_log_level_t log_level,
			 const char *format, ...) {
  va_list va_ap;
  struct tm result;

  if(log_level <= nDPI_LogLevel) {
    char buf[8192], out_buf[8192];
    char theDate[32];
    const char *extra_msg = "";
    time_t theTime = time(NULL);

    va_start (va_ap, format);

    if(log_level == NDPI_LOG_ERROR)
      extra_msg = "STR";
    else if(log_level == NDPI_LOG_TRACE)
      extra_msg = "STR";
    else
      extra_msg = "STR";

    memset(buf, 0, sizeof(buf));
    strftime(theDate, 32, "STR", localtime_r(&theTime,&result));
    vsnprintf(buf, sizeof(buf)-1, format, va_ap);

    snprintf(out_buf, sizeof(out_buf), "STR", theDate, extra_msg, buf);
    printf("STR", out_buf);
    fflush(stdout);
  }

  va_end(va_ap);
}