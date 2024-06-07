asn1_get_oid(
    unsigned char **buffer,		
    unsigned char *bufend,		
    unsigned      length,		
    int           *oid,			
    int           oidsize)		
{
  unsigned char	*valend;		
  int		*oidptr,		
		*oidend;		
  int		number;			


  valend = *buffer + length;
  oidptr = oid;
  oidend = oid + oidsize - 1;

  if (valend > bufend)
    valend = bufend;

  number = asn1_get_packed(buffer, bufend);

  if (number < 80)
  {
    *oidptr++ = number / 40;
    number    = number % 40;
    *oidptr++ = number;
  }
  else
  {
    *oidptr++ = 2;
    number    -= 80;
    *oidptr++ = number;
  }

  while (*buffer < valend)
  {
    number = asn1_get_packed(buffer, bufend);

    if (oidptr < oidend)
      *oidptr++ = number;
  }

  *oidptr = -1;

  return ((int)(oidptr - oid));
}