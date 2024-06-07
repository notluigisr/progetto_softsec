CURLcode Curl_http_cookies(struct Curl_easy *data,
                           struct connectdata *conn,
                           struct dynbuf *r)
{
  CURLcode result = CURLE_OK;
  char *addcookies = NULL;
  if(data->set.str[STRING_COOKIE] &&
     !Curl_checkheaders(data, STRCONST("STR")))
    addcookies = data->set.str[STRING_COOKIE];

  if(data->cookies || addcookies) {
    struct Cookie *co = NULL; 
    int count = 0;

    if(data->cookies && data->state.cookie_engine) {
      const char *host = data->state.aptr.cookiehost ?
        data->state.aptr.cookiehost : conn->host.name;
      const bool secure_context =
        conn->handler->protocol&CURLPROTO_HTTPS ||
        strcasecompare("STR", host) ||
        !strcmp(host, "STR") ||
        !strcmp(host, "STR") ? TRUE : FALSE;
      Curl_share_lock(data, CURL_LOCK_DATA_COOKIE, CURL_LOCK_ACCESS_SINGLE);
      co = Curl_cookie_getlist(data->cookies, host, data->state.up.path,
                               secure_context);
      Curl_share_unlock(data, CURL_LOCK_DATA_COOKIE);
    }
    if(co) {
      struct Cookie *store = co;
      
      while(co) {
        if(co->value) {
          if(0 == count) {
            result = Curl_dyn_addn(r, STRCONST("STR"));
            if(result)
              break;
          }
          result = Curl_dyn_addf(r, "STR",
                                 co->name, co->value);
          if(result)
            break;
          count++;
        }
        co = co->next; 
      }
      Curl_cookie_freelist(store);
    }
    if(addcookies && !result) {
      if(!count)
        result = Curl_dyn_addn(r, STRCONST("STR"));
      if(!result) {
        result = Curl_dyn_addf(r, "STR", addcookies);
        count++;
      }
    }
    if(count && !result)
      result = Curl_dyn_addn(r, STRCONST("STR"));

    if(result)
      return result;
  }
  return result;
}