onig_get_retry_limit_in_match(void)
{
#ifdef USE_RETRY_LIMIT_IN_MATCH
  return RetryLimitInMatch;
#else
  
  return 0;
#endif
}