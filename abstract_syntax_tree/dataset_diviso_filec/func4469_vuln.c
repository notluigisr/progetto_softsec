CURLcode Curl_dupset(struct SessionHandle *dst, struct SessionHandle *src)
{
  CURLcode result = CURLE_OK;
  enum dupstring i;

  
  dst->set = src->set;

  
  memset(dst->set.str, 0, STRING_LAST * sizeof(char *));

  
  for(i=(enum dupstring)0; i< STRING_LAST; i++) {
    result = setstropt(&dst->set.str[i], src->set.str[i]);
    if(result)
      break;
  }

  
  return result;
}