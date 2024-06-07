_tor_strndup(const char *s, size_t n DMALLOC_PARAMS)
{
  char *dup;
  tor_assert(s);
  tor_assert(n < SIZE_T_CEILING);
  dup = _tor_malloc((n+1) DMALLOC_FN_ARGS);
  
  strncpy(dup, s, n);
  dup[n]='\0';
  return dup;
}