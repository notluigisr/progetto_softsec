register_application (SpiBridge * app)
{
  DBusMessage *message;
  DBusMessageIter iter;
  DBusError error;
  DBusPendingCall *pending;
  const int max_addr_length = 128; 

  dbus_error_init (&error);

  
  app->desktop_name = ATSPI_DBUS_NAME_REGISTRY;
  app->desktop_path = ATSPI_DBUS_PATH_ROOT;

  message = dbus_message_new_method_call (SPI_DBUS_NAME_REGISTRY,
                                          ATSPI_DBUS_PATH_ROOT,
                                          ATSPI_DBUS_INTERFACE_SOCKET,
                                          "STR");

  dbus_message_iter_init_append (message, &iter);
  spi_object_append_reference (&iter, app->root);
  
    if (!dbus_connection_send_with_reply (app->bus, message, &pending, -1)
        || !pending)
    {
        return FALSE;
    }

    dbus_pending_call_set_notify (pending, register_reply, app, NULL);

  if (message)
    dbus_message_unref (message);

  
  
  mkdir ("STR", S_IRWXU|S_IRWXG|S_IRWXO|S_ISVTX);
  chmod ("STR", S_IRWXU|S_IRWXG|S_IRWXO|S_ISVTX);
  app->app_bus_addr = g_malloc(max_addr_length * sizeof(char));
#ifndef DISABLE_P2P
  sprintf (app->app_bus_addr, "STR", getpid(),
           rand());
#else
  app->app_bus_addr [0] = '\0';
#endif

  return TRUE;
}