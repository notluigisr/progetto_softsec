static CURLcode bearssl_connect_step3(struct Curl_easy *data,
                                      struct connectdata *conn, int sockindex)
{
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  struct ssl_backend_data *backend = connssl->backend;
  CURLcode ret;

  DEBUGASSERT(ssl_connect_3 == connssl->connecting_state);

  if(conn->bits.tls_enable_alpn) {
    const char *protocol;

    protocol = br_ssl_engine_get_selected_protocol(&backend->ctx.eng);
    if(protocol) {
      infof(data, "STR", protocol);

#ifdef USE_NGHTTP2
      if(!strcmp(protocol, NGHTTP2_PROTO_VERSION_ID))
        conn->negnpn = CURL_HTTP_VERSION_2;
      else
#endif
      if(!strcmp(protocol, ALPN_HTTP_1_1))
        conn->negnpn = CURL_HTTP_VERSION_1_1;
      else
        infof(data, "STR", protocol);
      Curl_multiuse_state(data, conn->negnpn == CURL_HTTP_VERSION_2 ?
                          BUNDLE_MULTIPLEX : BUNDLE_NO_MULTIUSE);
    }
    else
      infof(data, "STR");
  }

  if(SSL_SET_OPTION(primary.sessionid)) {
    bool incache;
    void *oldsession;
    br_ssl_session_parameters *session;

    session = malloc(sizeof(*session));
    if(!session)
      return CURLE_OUT_OF_MEMORY;
    br_ssl_engine_get_session_parameters(&backend->ctx.eng, session);
    Curl_ssl_sessionid_lock(data);
    incache = !(Curl_ssl_getsessionid(data, conn,
                                      &oldsession, NULL, sockindex));
    if(incache)
      Curl_ssl_delsessionid(data, oldsession);
    ret = Curl_ssl_addsessionid(data, conn, session, 0, sockindex);
    Curl_ssl_sessionid_unlock(data);
    if(ret) {
      free(session);
      return CURLE_OUT_OF_MEMORY;
    }
  }

  connssl->connecting_state = ssl_connect_done;

  return CURLE_OK;
}