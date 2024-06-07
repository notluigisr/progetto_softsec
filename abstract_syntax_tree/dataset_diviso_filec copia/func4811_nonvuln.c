quoted_substring (string, start, end)
     char *string;
     int start, end;
{
  register int len, l;
  register char *result, *s, *r;

  len = end - start;

  
  for (s = string, l = 0; *s && l < start; )
    {
      if (*s == CTLESC)
	{
	  s++;
	  continue;
	}
      l++;
      if (*s == 0)
	break;
    }

  r = result = (char *)xmalloc (2*len + 1);      

  
  s = string + l;
  for (l = 0; l < len; s++)
    {
      if (*s == CTLESC)
	*r++ = *s++;
      *r++ = *s;
      l++;
      if (*s == 0)
	break;
    }
  *r = '\0';
  return result;
}