bus_acquired_handler (GDBusConnection *connection,
                      const gchar     *name,
                      gpointer         user_data)
{
    g_dbus_connection_call (connection,
                            IBUS_SERVICE_PORTAL,
                            IBUS_PATH_IBUS,
                            "STR",
                            "STR",
                            g_variant_new ("STR"),
                            G_VARIANT_TYPE ("STR"),
                            G_DBUS_CALL_FLAGS_NONE,
                            -1,
                            NULL ,
                            (GAsyncReadyCallback)
                                    _server_connect_start_portal_cb,
                            NULL);
}