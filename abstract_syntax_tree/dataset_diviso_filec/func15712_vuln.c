static CURLcode hsts_pull(struct Curl_easy *data, struct hsts *h)
{
  
  if(data->set.hsts_read) {
    CURLSTScode sc;
    DEBUGASSERT(h);
    do {
      char buffer[257];
      struct curl_hstsentry e;
      e.name = buffer;
      e.namelen = sizeof(buffer)-1;
      e.includeSubDomains = FALSE; 
      e.expire[0] = 0;
      e.name[0] = 0; 
      sc = data->set.hsts_read(data, &e, data->set.hsts_read_userp);
      if(sc == CURLSTS_OK) {
        time_t expires;
        CURLcode result;
        if(!e.name[0])
          
          return CURLE_BAD_FUNCTION_ARGUMENT;
        if(e.expire[0])
          expires = Curl_getdate_capped(e.expire);
        else
          expires = TIME_T_MAX; 
        result = hsts_create(h, e.name,
                             
                             e.includeSubDomains ? TRUE : FALSE,
                             expires);
        if(result)
          return result;
      }
      else if(sc == CURLSTS_FAIL)
        return CURLE_ABORTED_BY_CALLBACK;
    } while(sc == CURLSTS_OK);
  }
  return CURLE_OK;
}