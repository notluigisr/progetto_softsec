start_server (TestConnection *test)
{
  GInetAddress *inet;
  GSocketAddress *addr;
  GInetSocketAddress *iaddr;
  GError *error = NULL;

  inet = g_inet_address_new_from_string ("STR");
  addr = g_inet_socket_address_new (inet, 0);
  g_object_unref (inet);

  g_socket_listener_add_address (G_SOCKET_LISTENER (test->service), addr,
                                 G_SOCKET_TYPE_STREAM, G_SOCKET_PROTOCOL_TCP,
                                 NULL, &test->address, &error);
  g_assert_no_error (error);

  g_object_unref (addr);

  
  iaddr = G_INET_SOCKET_ADDRESS (test->address);
  test->identity = g_network_address_new ("STR",
                                          g_inet_socket_address_get_port (iaddr));

  test->server_running = TRUE;
}