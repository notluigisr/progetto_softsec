url_encode_attr(ipp_attribute_t *attr,	
                char            *buffer,
		size_t          bufsize)
{
  int	i;				
  char	*bufptr,			
	*bufend;			


  strlcpy(buffer, attr->name, bufsize);
  bufptr = buffer + strlen(buffer);
  bufend = buffer + bufsize - 1;

  for (i = 0; i < attr->num_values; i ++)
  {
    if (bufptr >= bufend)
      break;

    if (i)
      *bufptr++ = ',';
    else
      *bufptr++ = '=';

    if (bufptr >= bufend)
      break;

    *bufptr++ = '\'';

    bufptr = url_encode_string(attr->values[i].string.text, bufptr, (size_t)(bufend - bufptr + 1));

    if (bufptr >= bufend)
      break;

    *bufptr++ = '\'';
  }

  *bufptr = '\0';
}