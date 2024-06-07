bus_new_connection_cb (GDBusServer     *server,
                       GDBusConnection *dbus_connection,
                       gpointer         user_data)
{
    BusConnection *connection = bus_connection_new (dbus_connection);
    bus_dbus_impl_new_connection (dbus, connection);

    if (g_object_is_floating (connection)) {
        
        ibus_object_destroy ((IBusObject *)connection);
        g_object_unref (connection);
    }
    return TRUE;
}