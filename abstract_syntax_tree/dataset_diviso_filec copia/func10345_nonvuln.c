static CURLcode mbedtls_connect(struct Curl_easy *data,
                                struct connectdata *conn, int sockindex)
{
  CURLcode retcode;
  bool done = FALSE;

  retcode = mbed_connect_common(data, conn, sockindex, FALSE, &done);
  if(retcode)
    return retcode;

  DEBUGASSERT(done);

  return CURLE_OK;
}