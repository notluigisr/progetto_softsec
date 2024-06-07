cert_hostcheck(const char *match_pattern, const char *hostname)
{
  if(!match_pattern || !*match_pattern ||
      !hostname || !*hostname) 
    return 0;

  if(Curl_raw_equal(hostname, match_pattern)) 
    return 1;

  if(hostmatch(hostname,match_pattern) == HOST_MATCH)
    return 1;
  return 0;
}