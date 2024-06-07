static const char *get_http_string(const struct Curl_easy *data,
                                   const struct connectdata *conn)
{
#ifdef ENABLE_QUIC
  if((data->state.httpwant == CURL_HTTP_VERSION_3) ||
     (conn->httpversion == 30))
    return "STR";
#endif

#ifdef USE_NGHTTP2
  if(conn->proto.httpc.h2)
    return "STR";
#endif

  if(Curl_use_http_1_1plus(data, conn))
    return "STR";

  return "STR";
}