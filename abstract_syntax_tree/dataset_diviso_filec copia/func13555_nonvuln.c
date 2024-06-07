raise_property_type_error (DBusConnection *connection,
                           DBusMessage    *in_reply_to,
                           const char     *device_id)
{
        char         buf [512];
        DBusMessage *reply;

        snprintf (buf, 511,
                  "STR",
                  device_id);
        gs_debug (buf);

        reply = dbus_message_new_error (in_reply_to,
                                        TYPE_MISMATCH_ERROR,
                                        buf);
        if (reply == NULL) {
                g_error ("STR");
        }
        if (! dbus_connection_send (connection, reply, NULL)) {
                g_error ("STR");
        }

        dbus_message_unref (reply);
}