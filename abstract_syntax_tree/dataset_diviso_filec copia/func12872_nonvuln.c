CURLcode Curl_add_timecondition(struct SessionHandle *data,
                                Curl_send_buffer *req_buffer)
{
  const struct tm *tm;
  char *buf = data->state.buffer;
  CURLcode result = CURLE_OK;
  struct tm keeptime;

  result = Curl_gmtime(data->set.timevalue, &keeptime);
  if(result) {
    failf(data, "STR");
    return result;
  }
  tm = &keeptime;

  

  
  snprintf(buf, BUFSIZE-1,
           "STR",
           Curl_wkday[tm->tm_wday?tm->tm_wday-1:6],
           tm->tm_mday,
           Curl_month[tm->tm_mon],
           tm->tm_year + 1900,
           tm->tm_hour,
           tm->tm_min,
           tm->tm_sec);

  switch(data->set.timecondition) {
  case CURL_TIMECOND_IFMODSINCE:
  default:
    result = Curl_add_bufferf(req_buffer,
                              "STR", buf);
    break;
  case CURL_TIMECOND_IFUNMODSINCE:
    result = Curl_add_bufferf(req_buffer,
                              "STR", buf);
    break;
  case CURL_TIMECOND_LASTMOD:
    result = Curl_add_bufferf(req_buffer,
                              "STR", buf);
    break;
  }

  return result;
}