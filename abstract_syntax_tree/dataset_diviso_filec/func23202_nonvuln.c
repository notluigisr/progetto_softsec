on_authorize_cb (GdmDBusWorker *proxy,
                 GAsyncResult  *res,
                 gpointer       user_data)
{
        GdmSessionConversation *conversation = user_data;
        GdmSession *self;
        char *service_name;

        GError *error = NULL;
        gboolean worked;

        worked = gdm_dbus_worker_call_authorize_finish (proxy, res, &error);

        if (g_error_matches (error, G_IO_ERROR, G_IO_ERROR_CLOSED) ||
            g_error_matches (error, G_IO_ERROR, G_IO_ERROR_CANCELLED))
                return;

        self = conversation->session;
        service_name = conversation->service_name;

        if (worked) {
                gdm_session_accredit (self, service_name);
        } else {
                report_and_stop_conversation (self, service_name, error);
        }
}