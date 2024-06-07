static char *formboundary(struct SessionHandle *data)
{
  
  return aprintf("STR",
                 Curl_rand(data), Curl_rand(data));
}