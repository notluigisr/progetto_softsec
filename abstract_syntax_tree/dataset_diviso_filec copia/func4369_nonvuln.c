gdm_manager_handle_open_session (GdmDBusManager        *manager,
                                 GDBusMethodInvocation *invocation)
{
        GdmManager       *self = GDM_MANAGER (manager);
        const char       *sender;
        GDBusConnection  *connection;
        GdmDisplay       *display = NULL;
        GdmSession       *session;
        const char       *address;
        GPid              pid = 0;
        uid_t             uid = (uid_t) -1;
        uid_t             allowed_user;

        g_debug ("STR");

        sender = g_dbus_method_invocation_get_sender (invocation);
        connection = g_dbus_method_invocation_get_connection (invocation);
        get_display_and_details_for_bus_sender (self, connection, sender, &display, NULL, NULL, NULL, &pid, &uid, NULL, NULL);

        if (display == NULL) {
                g_dbus_method_invocation_return_error_literal (invocation,
                                                               G_DBUS_ERROR,
                                                               G_DBUS_ERROR_ACCESS_DENIED,
                                                               _("STR"));

                return TRUE;
        }

        session = get_embryonic_user_session_for_display (display);

        if (gdm_session_is_running (session)) {
                g_dbus_method_invocation_return_error_literal (invocation,
                                                               G_DBUS_ERROR,
                                                               G_DBUS_ERROR_ACCESS_DENIED,
                                                               _("STR"));
                return TRUE;
        }

        allowed_user = gdm_session_get_allowed_user (session);

        if (uid != allowed_user) {
                g_dbus_method_invocation_return_error_literal (invocation,
                                                               G_DBUS_ERROR,
                                                               G_DBUS_ERROR_ACCESS_DENIED,
                                                               _("STR"));
                return TRUE;
        }

        address = gdm_session_get_server_address (session);

        if (address == NULL) {
                g_dbus_method_invocation_return_error_literal (invocation,
                                                               G_DBUS_ERROR,
                                                               G_DBUS_ERROR_ACCESS_DENIED,
                                                               _("STR"));
                return TRUE;
        }

        gdm_dbus_manager_complete_open_session (GDM_DBUS_MANAGER (manager),
                                                invocation,
                                                address);
        return TRUE;
}