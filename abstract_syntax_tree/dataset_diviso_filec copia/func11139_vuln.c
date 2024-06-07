asn1_get_type(unsigned char **buffer,	
	      unsigned char *bufend)	
{
  int	type;				


  type = **buffer;
  (*buffer) ++;

  if ((type & 31) == 31)
    type = asn1_get_packed(buffer, bufend);

  return (type);
}