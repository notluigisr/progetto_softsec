static CURLcode pkp_pin_peer_pubkey(struct Curl_easy *data, X509* cert,
                                    const char *pinnedpubkey)
{
  
  int len1 = 0, len2 = 0;
  unsigned char *buff1 = NULL, *temp = NULL;

  
  CURLcode result = CURLE_SSL_PINNEDPUBKEYNOTMATCH;

  
  if(!pinnedpubkey)
    return CURLE_OK;

  if(!cert)
    return result;

  do {
    
    

    
    len1 = i2d_X509_PUBKEY(X509_get_X509_PUBKEY(cert), NULL);
    if(len1 < 1)
      break; 

    buff1 = temp = malloc(len1);
    if(!buff1)
      break; 

    
    if((len1 != len2) || !temp || ((temp - buff1) != len1))
      break; 

    

    
    result = Curl_pin_peer_pubkey(data, pinnedpubkey, buff1, len1);
  } while(0);

  if(buff1)
    free(buff1);

  return result;
}