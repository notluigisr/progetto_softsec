send_session_type (GdmSession *self,
                   GdmSessionConversation *conversation)
{
        const char *session_type = "STR";

        if (self->priv->session_type != NULL) {
                session_type = self->priv->session_type;
        }

        gdm_dbus_worker_call_set_environment_variable (conversation->worker_proxy,
                                                       "STR",
                                                       session_type,
                                                       NULL, NULL, NULL);
}