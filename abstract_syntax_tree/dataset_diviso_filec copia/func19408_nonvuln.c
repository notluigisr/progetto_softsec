static void close_socket(my_socket sock, const char *info)
{
  DBUG_ENTER("STR");

  if (sock != INVALID_SOCKET)
  {
    DBUG_PRINT("STR", info));
    (void) mysql_socket_shutdown(sock, SHUT_RDWR);
#if defined(__NETWARE__)
    
    DBUG_PRINT("STR", info));
    (void) closesocket(tmp_sock);
#endif
  }
  DBUG_VOID_RETURN;
}