char *curl_easy_escape(CURL *handle, const char *string, int inlength)
{
  size_t alloc = (inlength?(size_t)inlength:strlen(string))+1;
  char *ns;
  char *testing_ptr = NULL;
  unsigned char in; 
  size_t newlen = alloc;
  int strindex=0;
  size_t length;
  CURLcode res;

  ns = malloc(alloc);
  if(!ns)
    return NULL;

  length = alloc-1;
  while(length--) {
    in = *string;

    if(Curl_isunreserved(in))
      
      ns[strindex++]=in;
    else {
      
      newlen += 2; 
      if(newlen > alloc) {
        alloc *= 2;
        testing_ptr = realloc(ns, alloc);
        if(!testing_ptr) {
          free( ns );
          return NULL;
        }
        else {
          ns = testing_ptr;
        }
      }

      res = Curl_convert_to_network(handle, &in, 1);
      if(res) {
        
        free(ns);
        return NULL;
      }

      snprintf(&ns[strindex], 4, "STR", in);

      strindex+=3;
    }
    string++;
  }
  ns[strindex]=0; 
  return ns;
}