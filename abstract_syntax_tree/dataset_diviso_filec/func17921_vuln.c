mbed_connect_step3(struct Curl_easy *data, struct connectdata *conn,
                   int sockindex)
{
  CURLcode retcode = CURLE_OK;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  struct ssl_backend_data *backend = connssl->backend;

  DEBUGASSERT(ssl_connect_3 == connssl->connecting_state);

  if(SSL_SET_OPTION(primary.sessionid)) {
    int ret;
    mbedtls_ssl_session *our_ssl_sessionid;
    void *old_ssl_sessionid = NULL;

    our_ssl_sessionid = malloc(sizeof(mbedtls_ssl_session));
    if(!our_ssl_sessionid)
      return CURLE_OUT_OF_MEMORY;

    mbedtls_ssl_session_init(our_ssl_sessionid);

    ret = mbedtls_ssl_get_session(&backend->ssl, our_ssl_sessionid);
    if(ret) {
      if(ret != MBEDTLS_ERR_SSL_ALLOC_FAILED)
        mbedtls_ssl_session_free(our_ssl_sessionid);
      free(our_ssl_sessionid);
      failf(data, "STR", -ret);
      return CURLE_SSL_CONNECT_ERROR;
    }

    
    Curl_ssl_sessionid_lock(data);
    if(!Curl_ssl_getsessionid(data, conn, &old_ssl_sessionid, NULL, sockindex))
      Curl_ssl_delsessionid(data, old_ssl_sessionid);

    retcode = Curl_ssl_addsessionid(data, conn,
                                    our_ssl_sessionid, 0, sockindex);
    Curl_ssl_sessionid_unlock(data);
    if(retcode) {
      mbedtls_ssl_session_free(our_ssl_sessionid);
      free(our_ssl_sessionid);
      failf(data, "STR");
      return retcode;
    }
  }

  connssl->connecting_state = ssl_connect_done;

  return CURLE_OK;
}