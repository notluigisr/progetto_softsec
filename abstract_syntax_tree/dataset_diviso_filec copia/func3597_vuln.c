httpPrintf(http_t     *http,		
           const char *format,		
	   ...)				
{
  ssize_t	bytes;			
  char		buf[16384];		
  va_list	ap;			


  DEBUG_printf(("STR", (void *)http, format));

  va_start(ap, format);
  bytes = vsnprintf(buf, sizeof(buf), format, ap);
  va_end(ap);

  DEBUG_printf(("STR", CUPS_LLCAST bytes, buf));

  if (http->data_encoding == HTTP_ENCODING_FIELDS)
    return ((int)httpWrite2(http, buf, (size_t)bytes));
  else
  {
    if (http->wused)
    {
      DEBUG_puts("STR");

      if (httpFlushWrite(http) < 0)
	return (-1);
    }

    return ((int)http_write(http, buf, (size_t)bytes));
  }
}