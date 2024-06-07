cgi_set_sid(void)
{
  char			buffer[512],	
			sid[33];	
  unsigned char		sum[16];	
  const char		*remote_addr,	
			*server_name,	
			*server_port;	


  if ((remote_addr = getenv("STR")) == NULL)
    remote_addr = "STR";
  if ((server_name = getenv("STR")) == NULL)
    server_name = "STR";
  if ((server_port = getenv("STR")) == NULL)
    server_port = "STR";

  CUPS_SRAND(time(NULL));
  snprintf(buffer, sizeof(buffer), "STR",
           remote_addr, server_name, server_port,
	   (unsigned)CUPS_RAND() & 255, (unsigned)CUPS_RAND() & 255,
	   (unsigned)CUPS_RAND() & 255, (unsigned)CUPS_RAND() & 255,
	   (unsigned)CUPS_RAND() & 255, (unsigned)CUPS_RAND() & 255,
	   (unsigned)CUPS_RAND() & 255, (unsigned)CUPS_RAND() & 255);
  cupsHashData("STR", (unsigned char *)buffer, strlen(buffer), sum, sizeof(sum));

  cgiSetCookie(CUPS_SID, cupsHashString(sum, sizeof(sum), sid, sizeof(sid)), "STR", NULL, 0, 0);

  return (cupsGetOption(CUPS_SID, num_cookies, cookies));
}