static CURLcode wolfssl_connect_nonblocking(struct Curl_easy *data,
                                            struct connectdata *conn,
                                            int sockindex, bool *done)
{
  return wolfssl_connect_common(data, conn, sockindex, TRUE, done);
}