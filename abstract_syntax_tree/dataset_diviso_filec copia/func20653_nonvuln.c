sub_append_string (source, target, indx, size)
     char *source, *target;
     int *indx, *size;
{
  if (source)
    {
      int srclen, n;

      srclen = STRLEN (source);
      if (srclen >= (int)(*size - *indx))
	{
	  n = srclen + *indx;
	  n = (n + DEFAULT_ARRAY_SIZE) - (n % DEFAULT_ARRAY_SIZE);
	  target = (char *)xrealloc (target, (*size = n));
	}

      FASTCOPY (source, target + *indx, srclen);
      *indx += srclen;
      target[*indx] = '\0';

      free (source);
    }
  return (target);
}