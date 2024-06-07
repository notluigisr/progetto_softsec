client_conn_register_skeleton (GDBusConnection *dbus_conn,
                               gpointer value,
                               RegisteredPath *reg_path)
{
  peer_register_skeleton (reg_path->obj_path, reg_path, dbus_conn);
}