int mutt_ssl_socket_setup (CONNECTION * conn)
{
  if (ssl_init() < 0)
  {
    conn->conn_open = ssl_socket_open_err;
    return -1;
  }

  conn->conn_open	= ssl_socket_open;
  conn->conn_read	= ssl_socket_read;
  conn->conn_write	= ssl_socket_write;
  conn->conn_close	= ssl_socket_close;
  conn->conn_poll       = ssl_socket_poll;

  return 0;
}