convert_to_network(char *buffer, size_t length)
{
  CURLcode rc;

  
  char *input_ptr, *output_ptr;
  size_t in_bytes, out_bytes;

  
  if(outbound_cd == (iconv_t)-1) {
    outbound_cd = iconv_open(CURL_ICONV_CODESET_OF_NETWORK,
                             CURL_ICONV_CODESET_OF_HOST);
    if(outbound_cd == (iconv_t)-1) {
      return CURLE_CONV_FAILED;
    }
  }
  
  input_ptr = output_ptr = buffer;
  in_bytes = out_bytes = length;
  rc = iconv(outbound_cd, &input_ptr,  &in_bytes,
                          &output_ptr, &out_bytes);
  if ((rc == -1) || (in_bytes != 0)) {
    return CURLE_CONV_FAILED;
  }

  return CURLE_OK;
}