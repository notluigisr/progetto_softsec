select_next_proto_cb(SSL *ssl,
                     unsigned char **out, unsigned char *outlen,
                     const unsigned char *in, unsigned int inlen,
                     void *arg)
{
  struct Curl_easy *data = (struct Curl_easy *)arg;
  struct connectdata *conn = data->conn;
  (void)ssl;

#ifdef USE_NGHTTP2
  if(data->state.httpwant >= CURL_HTTP_VERSION_2 &&
     !select_next_protocol(out, outlen, in, inlen, NGHTTP2_PROTO_VERSION_ID,
                           NGHTTP2_PROTO_VERSION_ID_LEN)) {
    infof(data, "STR",
          NGHTTP2_PROTO_VERSION_ID);
    conn->negnpn = CURL_HTTP_VERSION_2;
    return SSL_TLSEXT_ERR_OK;
  }
#endif

  if(!select_next_protocol(out, outlen, in, inlen, ALPN_HTTP_1_1,
                           ALPN_HTTP_1_1_LENGTH)) {
    infof(data, "STR");
    conn->negnpn = CURL_HTTP_VERSION_1_1;
    return SSL_TLSEXT_ERR_OK;
  }

  infof(data, "STR");
  *out = (unsigned char *)ALPN_HTTP_1_1;
  *outlen = ALPN_HTTP_1_1_LENGTH;
  conn->negnpn = CURL_HTTP_VERSION_1_1;

  return SSL_TLSEXT_ERR_OK;
}