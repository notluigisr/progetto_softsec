static ssize_t wolfssl_send(struct Curl_easy *data,
                            int sockindex,
                            const void *mem,
                            size_t len,
                            CURLcode *curlcode)
{
  struct connectdata *conn = data->conn;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  struct ssl_backend_data *backend = connssl->backend;
  char error_buffer[WOLFSSL_MAX_ERROR_SZ];
  int memlen = (len > (size_t)INT_MAX) ? INT_MAX : (int)len;
  int rc = SSL_write(backend->handle, mem, memlen);

  if(rc < 0) {
    int err = SSL_get_error(backend->handle, rc);

    switch(err) {
    case SSL_ERROR_WANT_READ:
    case SSL_ERROR_WANT_WRITE:
      
      *curlcode = CURLE_AGAIN;
      return -1;
    default:
      failf(data, "STR",
            ERR_error_string(err, error_buffer),
            SOCKERRNO);
      *curlcode = CURLE_SEND_ERROR;
      return -1;
    }
  }
  return rc;
}