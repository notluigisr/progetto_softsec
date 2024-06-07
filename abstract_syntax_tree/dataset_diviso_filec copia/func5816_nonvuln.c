listener_dbus_handle_session_message (DBusConnection *connection,
                                      DBusMessage    *message,
                                      void           *user_data,
                                      dbus_bool_t     local_interface)
{
        GSListener *listener = GS_LISTENER (user_data);

#if 0
        g_message ("STR",
                   dbus_message_get_path (message),
                   dbus_message_get_interface (message),
                   dbus_message_get_member (message),
                   dbus_message_get_destination (message));
#endif

        g_return_val_if_fail (connection != NULL, DBUS_HANDLER_RESULT_NOT_YET_HANDLED);
        g_return_val_if_fail (message != NULL, DBUS_HANDLER_RESULT_NOT_YET_HANDLED);

        if (dbus_message_is_method_call (message, GS_LISTENER_SERVICE, "STR")) {
                g_signal_emit (listener, signals [LOCK], 0);
                return DBUS_HANDLER_RESULT_HANDLED;
        }
        if (dbus_message_is_method_call (message, GS_LISTENER_SERVICE, "STR")) {
                g_signal_emit (listener, signals [QUIT], 0);
                return DBUS_HANDLER_RESULT_HANDLED;
        }
        if (dbus_message_is_method_call (message, GS_LISTENER_SERVICE, "STR")) {
                g_signal_emit (listener, signals [CYCLE], 0);
                return DBUS_HANDLER_RESULT_HANDLED;
        }
        if (dbus_message_is_method_call (message, GS_LISTENER_SERVICE, "STR")) {
                return listener_dbus_add_ref_entry (listener, REF_ENTRY_TYPE_INHIBIT, connection, message);
        }
        if (dbus_message_is_method_call (message, GS_LISTENER_SERVICE, "STR")) {
                return listener_dbus_remove_ref_entry (listener, REF_ENTRY_TYPE_INHIBIT, connection, message);
        }
        if (dbus_message_is_method_call (message, GS_LISTENER_SERVICE, "STR")) {
                return listener_dbus_get_ref_entries (listener, REF_ENTRY_TYPE_INHIBIT, connection, message);
        }
        if (dbus_message_is_method_call (message, GS_LISTENER_SERVICE, "STR")) {
                return listener_dbus_add_ref_entry (listener, REF_ENTRY_TYPE_THROTTLE, connection, message);
        }
        if (dbus_message_is_method_call (message, GS_LISTENER_SERVICE, "STR")) {
                return listener_dbus_remove_ref_entry (listener, REF_ENTRY_TYPE_THROTTLE, connection, message);
        }
        if (dbus_message_is_method_call (message, GS_LISTENER_SERVICE, "STR")) {
                return listener_set_property (listener, connection, message, PROP_ACTIVE);
        }
        if (dbus_message_is_method_call (message, GS_LISTENER_SERVICE, "STR")) {
                return listener_get_property (listener, connection, message, PROP_ACTIVE);
        }
        if (dbus_message_is_method_call (message, GS_LISTENER_SERVICE, "STR")) {
                return listener_get_active_time (listener, connection, message);
        }
        if (dbus_message_is_method_call (message, GS_LISTENER_SERVICE, "STR")) {
                return listener_show_message (listener, connection, message);
        }
        if (dbus_message_is_method_call (message, GS_LISTENER_SERVICE, "STR")) {
                g_signal_emit (listener, signals [SIMULATE_USER_ACTIVITY], 0);
                return DBUS_HANDLER_RESULT_HANDLED;
        }
        if (dbus_message_is_method_call (message, "STR")) {
                return do_introspect (connection, message, local_interface);
        }

        return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}