static void conn_free(struct connectdata *conn)
{
  DEBUGASSERT(conn);

  Curl_free_idnconverted_hostname(&conn->host);
  Curl_free_idnconverted_hostname(&conn->conn_to_host);
#ifndef CURL_DISABLE_PROXY
  Curl_free_idnconverted_hostname(&conn->http_proxy.host);
  Curl_free_idnconverted_hostname(&conn->socks_proxy.host);
  Curl_safefree(conn->http_proxy.user);
  Curl_safefree(conn->socks_proxy.user);
  Curl_safefree(conn->http_proxy.passwd);
  Curl_safefree(conn->socks_proxy.passwd);
  Curl_safefree(conn->http_proxy.host.rawalloc); 
  Curl_safefree(conn->socks_proxy.host.rawalloc); 
  Curl_free_primary_ssl_config(&conn->proxy_ssl_config);
#endif
  Curl_safefree(conn->user);
  Curl_safefree(conn->passwd);
  Curl_safefree(conn->sasl_authzid);
  Curl_safefree(conn->options);
  Curl_dyn_free(&conn->trailer);
  Curl_safefree(conn->host.rawalloc); 
  Curl_safefree(conn->conn_to_host.rawalloc); 
  Curl_safefree(conn->hostname_resolve);
  Curl_safefree(conn->secondaryhostname);
  Curl_safefree(conn->connect_state);

  conn_reset_all_postponed_data(conn);
  Curl_llist_destroy(&conn->easyq, NULL);
  Curl_safefree(conn->localdev);
  Curl_free_primary_ssl_config(&conn->ssl_config);

#ifdef USE_UNIX_SOCKETS
  Curl_safefree(conn->unix_domain_socket);
#endif

#ifdef USE_SSL
  Curl_safefree(conn->ssl_extra);
#endif
  free(conn); 
}