static int ossl_new_session_cb(SSL *ssl, SSL_SESSION *ssl_sessionid)
{
  int res = 0;
  struct connectdata *conn;
  struct Curl_easy *data;
  int sockindex;
  curl_socket_t *sockindex_ptr;
  int data_idx = ossl_get_ssl_data_index();
  int connectdata_idx = ossl_get_ssl_conn_index();
  int sockindex_idx = ossl_get_ssl_sockindex_index();

  if(data_idx < 0 || connectdata_idx < 0 || sockindex_idx < 0)
    return 0;

  conn = (struct connectdata*) SSL_get_ex_data(ssl, connectdata_idx);
  if(!conn)
    return 0;

  data = (struct Curl_easy *) SSL_get_ex_data(ssl, data_idx);

  
  sockindex_ptr = (curl_socket_t*) SSL_get_ex_data(ssl, sockindex_idx);
  sockindex = (int)(sockindex_ptr - conn->sock);

  if(SSL_SET_OPTION(primary.sessionid)) {
    bool incache;
    void *old_ssl_sessionid = NULL;

    Curl_ssl_sessionid_lock(data);
    incache = !(Curl_ssl_getsessionid(data, conn, &old_ssl_sessionid, NULL,
                                      sockindex));
    if(incache) {
      if(old_ssl_sessionid != ssl_sessionid) {
        infof(data, "STR");
        Curl_ssl_delsessionid(data, old_ssl_sessionid);
        incache = FALSE;
      }
    }

    if(!incache) {
      if(!Curl_ssl_addsessionid(data, conn, ssl_sessionid,
                                      0 , sockindex)) {
        
        res = 1;
      }
      else
        failf(data, "STR");
    }
    Curl_ssl_sessionid_unlock(data);
  }

  return res;
}