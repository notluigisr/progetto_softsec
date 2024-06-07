daemon_new_connection_func (GDBusServer *server,
                            GDBusConnection *connection,
                            gpointer user_data)
{
  NewConnectionData *data;

  data = user_data;

  
  data->conn = g_object_ref (connection);

  daemon_peer_connection_setup (data->daemon, data->conn, data);

  
  g_dbus_server_stop (server);
  g_object_unref (server);
  
  return TRUE;
}