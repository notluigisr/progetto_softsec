asn1_get_packed(
    unsigned char **buffer,		
    unsigned char *bufend)		
{
  int	value;				


  value = 0;

  while ((**buffer & 128) && *buffer < bufend)
  {
    value = (value << 7) | (**buffer & 127);
    (*buffer) ++;
  }

  if (*buffer < bufend)
  {
    value = (value << 7) | **buffer;
    (*buffer) ++;
  }

  return (value);
}