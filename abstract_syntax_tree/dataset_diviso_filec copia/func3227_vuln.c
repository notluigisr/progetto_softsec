asn1_get_integer(
    unsigned char **buffer,		
    unsigned char *bufend,		
    unsigned      length)		
{
  int	value;				


  if (length > sizeof(int))
  {
    (*buffer) += length;
    return (0);
  }

  for (value = (**buffer & 0x80) ? -1 : 0;
       length > 0 && *buffer < bufend;
       length --, (*buffer) ++)
    value = (value << 8) | **buffer;

  return (value);
}