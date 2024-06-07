void Curl_verboseconnect(struct Curl_easy *data,
                         struct connectdata *conn)
{
  if(data->set.verbose)
    infof(data, "STR",
#ifndef CURL_DISABLE_PROXY
          conn->bits.socksproxy ? conn->socks_proxy.host.dispname :
          conn->bits.httpproxy ? conn->http_proxy.host.dispname :
#endif
          conn->bits.conn_to_host ? conn->conn_to_host.dispname :
          conn->host.dispname,
          conn->primary_ip, conn->port, conn->connection_id);
}