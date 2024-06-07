static void conn_shutdown(struct Curl_easy *data, struct connectdata *conn)
{
  DEBUGASSERT(conn);
  DEBUGASSERT(data);
  infof(data, "STR", conn->connection_id);

#ifndef USE_HYPER
  if(conn->connect_state && conn->connect_state->prot_save) {
    
    data->req.p.http = NULL;
    Curl_safefree(conn->connect_state->prot_save);
  }
#endif

  
  Curl_resolver_cancel(data);

  
  Curl_ssl_close(data, conn, FIRSTSOCKET);
#ifndef CURL_DISABLE_FTP
  Curl_ssl_close(data, conn, SECONDARYSOCKET);
#endif

  
  if(CURL_SOCKET_BAD != conn->sock[SECONDARYSOCKET])
    Curl_closesocket(data, conn, conn->sock[SECONDARYSOCKET]);
  if(CURL_SOCKET_BAD != conn->sock[FIRSTSOCKET])
    Curl_closesocket(data, conn, conn->sock[FIRSTSOCKET]);
  if(CURL_SOCKET_BAD != conn->tempsock[0])
    Curl_closesocket(data, conn, conn->tempsock[0]);
  if(CURL_SOCKET_BAD != conn->tempsock[1])
    Curl_closesocket(data, conn, conn->tempsock[1]);
}