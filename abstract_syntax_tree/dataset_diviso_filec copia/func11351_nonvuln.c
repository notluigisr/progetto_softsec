static CURLcode setstropt(char **charp, char *s)
{
  

  Curl_safefree(*charp);

  if(s) {
    s = strdup(s);

    if(!s)
      return CURLE_OUT_OF_MEMORY;

    *charp = s;
  }

  return CURLE_OK;
}