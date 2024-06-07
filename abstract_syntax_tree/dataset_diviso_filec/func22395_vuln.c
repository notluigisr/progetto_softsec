asn1_get_length(unsigned char **buffer,	
		unsigned char *bufend)	
{
  unsigned	length;			


  length = **buffer;
  (*buffer) ++;

  if (length & 128)
  {
    int	count;				


    if ((count = length & 127) > sizeof(unsigned))
    {
      (*buffer) += count;
      return (0);
    }

    for (length = 0;
	 count > 0 && *buffer < bufend;
	 count --, (*buffer) ++)
      length = (length << 8) | **buffer;
  }

  return (length);
}