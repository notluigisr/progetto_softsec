bool Curl_ssl_getsessionid(struct Curl_easy *data,
                           struct connectdata *conn,
                           void **ssl_sessionid,
                           size_t *idsize, 
                           int sockindex)
{
  struct Curl_ssl_session *check;
  size_t i;
  long *general_age;
  bool no_match = TRUE;

#ifndef CURL_DISABLE_PROXY
  const bool isProxy = CONNECT_PROXY_SSL();
  struct ssl_primary_config * const ssl_config = isProxy ?
    &conn->proxy_ssl_config :
    &conn->ssl_config;
  const char * const name = isProxy ?
    conn->http_proxy.host.name : conn->host.name;
  int port = isProxy ? (int)conn->port : conn->remote_port;
#else
  
  struct ssl_primary_config * const ssl_config = &conn->ssl_config;
  const char * const name = conn->host.name;
  int port = conn->remote_port;
  (void)sockindex;
#endif
  *ssl_sessionid = NULL;

  DEBUGASSERT(SSL_SET_OPTION(primary.sessionid));

  if(!SSL_SET_OPTION(primary.sessionid))
    
    return TRUE;

  
  if(SSLSESSION_SHARED(data))
    general_age = &data->share->sessionage;
  else
    general_age = &data->state.sessionage;

  for(i = 0; i < data->set.general_ssl.max_ssl_sessions; i++) {
    check = &data->state.session[i];
    if(!check->sessionid)
      
      continue;
    if(strcasecompare(name, check->name) &&
       ((!conn->bits.conn_to_host && !check->conn_to_host) ||
        (conn->bits.conn_to_host && check->conn_to_host &&
         strcasecompare(conn->conn_to_host.name, check->conn_to_host))) &&
       ((!conn->bits.conn_to_port && check->conn_to_port == -1) ||
        (conn->bits.conn_to_port && check->conn_to_port != -1 &&
         conn->conn_to_port == check->conn_to_port)) &&
       (port == check->remote_port) &&
       strcasecompare(conn->handler->scheme, check->scheme) &&
       Curl_ssl_config_matches(ssl_config, &check->ssl_config)) {
      
      (*general_age)++;          
      check->age = *general_age; 
      *ssl_sessionid = check->sessionid;
      if(idsize)
        *idsize = check->idsize;
      no_match = FALSE;
      break;
    }
  }

  return no_match;
}