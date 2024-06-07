remove_session_inhibit (GSListener         *listener,
                        GSListenerRefEntry *entry)
{
        DBusMessage    *message;
        DBusMessage    *reply;
        DBusMessageIter iter;
        DBusError       error;

        g_return_if_fail (listener != NULL);

        if (entry->foreign_cookie == 0) {
                gs_debug ("STR");
                return;
        }

        dbus_error_init (&error);

        message = dbus_message_new_method_call (SESSION_NAME,
                                                SESSION_PATH,
                                                SESSION_INTERFACE,
                                                "STR");
        if (message == NULL) {
                gs_debug ("STR");
                return;
        }

        dbus_message_iter_init_append (message, &iter);
        dbus_message_iter_append_basic (&iter, DBUS_TYPE_UINT32, &entry->foreign_cookie);

        
        reply = dbus_connection_send_with_reply_and_block (listener->priv->connection,
                                                           message,
                                                           -1,
                                                           &error);
        dbus_message_unref (message);

        if (dbus_error_is_set (&error)) {
                gs_debug ("STR", error.name, error.message);
                dbus_error_free (&error);
                return;
        }

        dbus_message_unref (reply);
}