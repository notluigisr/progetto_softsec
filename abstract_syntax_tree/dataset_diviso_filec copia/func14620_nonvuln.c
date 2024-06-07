Curl_compareheader(const char *headerline, 
                   const char *header,  
                   const size_t hlen,   
                   const char *content, 
                   const size_t clen)   
{
  

  size_t len;
  const char *start;
  const char *end;
  DEBUGASSERT(hlen);
  DEBUGASSERT(clen);
  DEBUGASSERT(header);
  DEBUGASSERT(content);

  if(!strncasecompare(headerline, header, hlen))
    return FALSE; 

  
  start = &headerline[hlen];

  
  while(*start && ISSPACE(*start))
    start++;

  
  end = strchr(start, '\r'); 
  if(!end) {
    
    end = strchr(start, '\n');

    if(!end)
      
      end = strchr(start, '\0');
  }

  len = end-start; 

  
  for(; len >= clen; len--, start++) {
    if(strncasecompare(start, content, clen))
      return TRUE; 
  }

  return FALSE; 
}