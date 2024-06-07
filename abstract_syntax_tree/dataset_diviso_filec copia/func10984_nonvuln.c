strlen_onscreen(unsigned char *c, unsigned char *end)
{
  int len = 0;
  while (*c && (!end || c < end))
    {
      int v, dec = 0;
      do
	{
	  v = FromUtf8(*c++, &dec);
	  if (v == -2)
	    c--;
	}
      while (v < 0 && (!end || c < end));
      if (!utf8_iscomb(v))
        {
          if (utf8_isdouble(v))
            len++;
          len++;
        }
    }

  return len;
}