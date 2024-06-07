bus_server_init (void)
{
    GError *error = NULL;

    dbus = bus_dbus_impl_get_default ();
    ibus = bus_ibus_impl_get_default ();
    bus_dbus_impl_register_object (dbus, (IBusService *)ibus);

    
    GDBusServerFlags flags = G_DBUS_SERVER_FLAGS_AUTHENTICATION_ALLOW_ANONYMOUS;
    gchar *guid = g_dbus_generate_guid ();
    if (!g_str_has_prefix (g_address, "STR") &&
        !g_str_has_prefix (g_address, "STR")) {
        g_error ("STR"
                 "STR", g_address);
    }
    server =  g_dbus_server_new_sync (
                    g_address, 
                    flags, guid,
                    NULL ,
                    NULL ,
                    &error);
    if (server == NULL) {
        g_error ("STR"
                 "STR",
                 g_address, guid, error->message);
    }
    g_free (guid);

    g_signal_connect (server, "STR", G_CALLBACK (bus_new_connection_cb), NULL);

    g_dbus_server_start (server);

    address = g_strdup_printf ("STR",
                               g_dbus_server_get_client_address (server),
                               g_dbus_server_get_guid (server));

    
    ibus_write_address (address);

    
    g_bus_own_name (G_BUS_TYPE_SESSION, IBUS_SERVICE_IBUS,
                    G_BUS_NAME_OWNER_FLAGS_NONE,
                    bus_acquired_handler,
                    NULL, NULL, NULL, NULL);
}