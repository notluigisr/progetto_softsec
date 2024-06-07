static ssize_t bearssl_recv(struct Curl_easy *data, int sockindex,
                            char *buf, size_t len, CURLcode *err)
{
  struct connectdata *conn = data->conn;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  struct ssl_backend_data *backend = connssl->backend;
  unsigned char *app;
  size_t applen;

  *err = bearssl_run_until(data, conn, sockindex, BR_SSL_RECVAPP);
  if(*err != CURLE_OK)
    return -1;
  app = br_ssl_engine_recvapp_buf(&backend->ctx.eng, &applen);
  if(!app)
    return 0;
  if(applen > len)
    applen = len;
  memcpy(buf, app, applen);
  br_ssl_engine_recvapp_ack(&backend->ctx.eng, applen);

  return applen;
}