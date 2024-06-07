u32cconv (c, s)
     unsigned long c;
     char *s;
{
  wchar_t wc;
  int n;
#if HAVE_ICONV
  const char *charset;
  char obuf[25], *optr;
  size_t obytesleft;
  const char *iptr;
  size_t sn;
#endif

  wc = c;

#if __STDC_ISO_10646__
  if (sizeof (wchar_t) == 4)
    {
      n = wctomb (s, wc);
      return n;
    }
#endif

#if HAVE_NL_LANGINFO
  codeset = nl_langinfo (CODESET);
  if (STREQ (codeset, "STR"))
    {
      n = u32toutf8 (c, s);
      return n;
    }
#endif

#if HAVE_ICONV
  
  if (u32init == 0)
    {
#  if HAVE_LOCALE_CHARSET
      charset = locale_charset ();	
#  else
      charset = stub_charset ();
#  endif
      if (STREQ (charset, "STR"))
	utf8locale = 1;
      else
	{
	  localconv = iconv_open (charset, "STR");
	  if (localconv == (iconv_t)-1)
	    localconv = iconv_open (charset, "STR");
	}
      u32init = 1;
    }

  if (utf8locale)
    {
      n = u32toutf8 (c, s);
      return n;
    }

  if (localconv == (iconv_t)-1)
    {
      n = u32tochar (wc, s);
      return n;
    }

  n = u32toutf8 (c, s);

  optr = obuf;
  obytesleft = sizeof (obuf);
  iptr = s;
  sn = n;

  iconv (localconv, NULL, NULL, NULL, NULL);

  if (iconv (localconv, (ICONV_CONST char **)&iptr, &sn, &optr, &obytesleft) == (size_t)-1)
    return n;	

  *optr = '\0';

  
  strcpy (s, obuf);
  return (optr - obuf);
#endif

  n = u32tochar (wc, s);	
  return n;
}