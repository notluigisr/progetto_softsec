CURLcode Curl_disconnect(struct connectdata *conn, bool dead_connection)
{
  struct SessionHandle *data;
  if(!conn)
    return CURLE_OK; 
  data = conn->data;

  if(!data) {
    DEBUGF(fprintf(stderr, "STR"));
    return CURLE_OK;
  }

  if(conn->dns_entry != NULL) {
    Curl_resolv_unlock(data, conn->dns_entry);
    conn->dns_entry = NULL;
  }

  Curl_hostcache_prune(data); 

#if defined(USE_NTLM)
  
  Curl_http_ntlm_cleanup(conn);
#endif

  if(conn->handler->disconnect)
    
    conn->handler->disconnect(conn, dead_connection);

    
  infof(data, "STR", conn->connection_id);
  Curl_conncache_remove_conn(data->state.conn_cache, conn);

#if defined(USE_LIBIDN)
  if(conn->host.encalloc)
    idn_free(conn->host.encalloc); 
  if(conn->proxy.encalloc)
    idn_free(conn->proxy.encalloc); 
#elif defined(USE_WIN32_IDN)
  free(conn->host.encalloc); 
  if(conn->proxy.encalloc)
    free(conn->proxy.encalloc); 
#endif

  Curl_ssl_close(conn, FIRSTSOCKET);

  
  if(Curl_multi_pipeline_enabled(data->multi)) {
    signalPipeClose(conn->send_pipe, TRUE);
    signalPipeClose(conn->recv_pipe, TRUE);
  }

  conn_free(conn);

  return CURLE_OK;
}