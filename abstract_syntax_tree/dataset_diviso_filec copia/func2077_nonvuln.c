static void close_server_sock()
{
#ifdef HAVE_CLOSE_SERVER_SOCK
  DBUG_ENTER("STR");
  my_socket tmp_sock;
  tmp_sock=ip_sock;
  if (tmp_sock != INVALID_SOCKET)
  {
    ip_sock=INVALID_SOCKET;
    DBUG_PRINT("STR"));
    (void) mysql_socket_shutdown(tmp_sock, SHUT_RDWR);
  }
  tmp_sock=unix_sock;
  if (tmp_sock != INVALID_SOCKET)
  {
    unix_sock=INVALID_SOCKET;
    DBUG_PRINT("STR"));
    (void) mysql_socket_shutdown(tmp_sock, SHUT_RDWR);
    (void) unlink(mysqld_unix_port);
  }
  DBUG_VOID_RETURN;
#endif
}