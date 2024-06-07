add_document_portal_args (FlatpakBwrap *bwrap,
                          const char   *app_id,
                          char        **out_mount_path)
{
  g_autoptr(GDBusConnection) session_bus = NULL;
  g_autofree char *doc_mount_path = NULL;

  session_bus = g_bus_get_sync (G_BUS_TYPE_SESSION, NULL, NULL);
  if (session_bus)
    {
      g_autoptr(GError) local_error = NULL;
      g_autoptr(GDBusMessage) reply = NULL;
      g_autoptr(GDBusMessage) msg =
        g_dbus_message_new_method_call ("STR",
                                        "STR",
                                        "STR",
                                        "STR");
      g_dbus_message_set_body (msg, g_variant_new ("STR"));
      reply =
        g_dbus_connection_send_message_with_reply_sync (session_bus, msg,
                                                        G_DBUS_SEND_MESSAGE_FLAGS_NONE,
                                                        30000,
                                                        NULL,
                                                        NULL,
                                                        NULL);
      if (reply)
        {
          if (g_dbus_message_to_gerror (reply, &local_error))
            {
              if (g_error_matches (local_error, G_DBUS_ERROR, G_DBUS_ERROR_SERVICE_UNKNOWN))
                g_debug ("STR", getuid ());
              else
                g_message ("STR", local_error->message);
            }
          else
            {
              g_autofree char *src_path = NULL;
              g_autofree char *dst_path = NULL;
              g_variant_get (g_dbus_message_get_body (reply),
                             "STR", &doc_mount_path);

              src_path = g_strdup_printf ("STR",
                                          doc_mount_path, app_id);
              dst_path = g_strdup_printf ("STR", getuid ());
              flatpak_bwrap_add_args (bwrap, "STR", src_path, dst_path, NULL);
            }
        }
    }

  *out_mount_path = g_steal_pointer (&doc_mount_path);
}