static void reuse_conn(struct connectdata *old_conn,
                       struct connectdata *conn)
{
  free(old_conn->proxy.rawalloc);

  
  Curl_free_ssl_config(&old_conn->ssl_config);

  conn->data = old_conn->data;

  
  conn->bits.user_passwd = old_conn->bits.user_passwd;
  if(conn->bits.user_passwd) {
    
    Curl_safefree(conn->user);
    Curl_safefree(conn->passwd);
    conn->user = old_conn->user;
    conn->passwd = old_conn->passwd;
    old_conn->user = NULL;
    old_conn->passwd = NULL;
  }

  conn->bits.proxy_user_passwd = old_conn->bits.proxy_user_passwd;
  if(conn->bits.proxy_user_passwd) {
    
    Curl_safefree(conn->proxyuser);
    Curl_safefree(conn->proxypasswd);
    conn->proxyuser = old_conn->proxyuser;
    conn->proxypasswd = old_conn->proxypasswd;
    old_conn->proxyuser = NULL;
    old_conn->proxypasswd = NULL;
  }

  
  Curl_safefree(conn->host.rawalloc);
  conn->host=old_conn->host;

  
  Curl_persistconninfo(conn);

  
  conn->bits.reuse = TRUE; 

  Curl_safefree(old_conn->user);
  Curl_safefree(old_conn->passwd);
  Curl_safefree(old_conn->proxyuser);
  Curl_safefree(old_conn->proxypasswd);
  Curl_safefree(old_conn->localdev);

  Curl_llist_destroy(old_conn->send_pipe, NULL);
  Curl_llist_destroy(old_conn->recv_pipe, NULL);

  old_conn->send_pipe = NULL;
  old_conn->recv_pipe = NULL;

  Curl_safefree(old_conn->master_buffer);
}