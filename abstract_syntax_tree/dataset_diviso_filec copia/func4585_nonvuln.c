glob_pattern_p (pattern)
     const char *pattern;
{
#if HANDLE_MULTIBYTE
  size_t n;
  wchar_t *wpattern;
  int r;

  if (MB_CUR_MAX == 1 || mbsmbchar (pattern) == 0)
    return (internal_glob_pattern_p ((unsigned char *)pattern));

  
  n = xdupmbstowcs (&wpattern, NULL, pattern);
  if (n == (size_t)-1)
    
    return (internal_glob_pattern_p ((unsigned char *)pattern));

  r = internal_glob_wpattern_p (wpattern);
  free (wpattern);

  return r;
#else
  return (internal_glob_pattern_p ((unsigned char *)pattern));
#endif
}