CURLcode Curl_dupset(struct SessionHandle *dst, struct SessionHandle *src)
{
  CURLcode result = CURLE_OK;
  enum dupstring i;

  
  dst->set = src->set;

  
  memset(dst->set.str, 0, STRING_LAST * sizeof(char *));

  
  for(i=(enum dupstring)0; i< STRING_LASTZEROTERMINATED; i++) {
    result = setstropt(&dst->set.str[i], src->set.str[i]);
    if(result)
      return result;
  }

  
  i = STRING_COPYPOSTFIELDS;
  if(src->set.postfieldsize && src->set.str[i]) {
    
    dst->set.str[i] = Curl_memdup(src->set.str[i],
                                  curlx_sotouz(src->set.postfieldsize));
    if(!dst->set.str[i])
      return CURLE_OUT_OF_MEMORY;
    
    dst->set.postfields = dst->set.str[i];
  }

  return CURLE_OK;
}