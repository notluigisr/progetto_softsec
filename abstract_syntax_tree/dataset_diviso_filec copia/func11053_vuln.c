asn1_get_string(
    unsigned char **buffer,		
    unsigned char *bufend,		
    unsigned      length,		
    char          *string,		
    size_t        strsize)		
{
  if (length > (unsigned)(bufend - *buffer))
    length = (unsigned)(bufend - *buffer);

  if (length < strsize)
  {
   

    if (length > 0)
      memcpy(string, *buffer, length);

    string[length] = '\0';
  }
  else
  {
   

    memcpy(string, *buffer, strsize - 1);
    string[strsize - 1] = '\0';
  }

  if (length > 0)
    (*buffer) += length;

  return (string);
}