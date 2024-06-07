mesalink_connect_step3(struct connectdata *conn, int sockindex)
{
  CURLcode result = CURLE_OK;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];

  DEBUGASSERT(ssl_connect_3 == connssl->connecting_state);

#ifdef MESALINK_HAVE_SESSION
  if(SSL_SET_OPTION(primary.sessionid)) {
    bool incache;
    SSL_SESSION *our_ssl_sessionid;
    void *old_ssl_sessionid = NULL;

    our_ssl_sessionid = SSL_get_session(BACKEND->handle);

    Curl_ssl_sessionid_lock(data);
    incache =
      !(Curl_ssl_getsessionid(data, conn,
                              &old_ssl_sessionid, NULL, sockindex));
    if(incache) {
      if(old_ssl_sessionid != our_ssl_sessionid) {
        infof(data, "STR");
        Curl_ssl_delsessionid(data, old_ssl_sessionid);
        incache = FALSE;
      }
    }

    if(!incache) {
      result = Curl_ssl_addsessionid(
        data, conn, our_ssl_sessionid, 0 , sockindex);
      if(result) {
        Curl_ssl_sessionid_unlock(data);
        failf(data, "STR");
        return result;
      }
    }
    Curl_ssl_sessionid_unlock(data);
  }
#endif 

  connssl->connecting_state = ssl_connect_done;

  return result;
}