bus_authorize_authenticated_peer_cb (GDBusAuthObserver     *observer,
                                     GIOStream             *stream,
                                     GCredentials          *credentials,
                                     G_GNUC_UNUSED gpointer user_data)
{
    gboolean authorized = FALSE;
    if (credentials) {
        GCredentials *own_credentials = g_credentials_new ();
        if (g_credentials_is_same_user (credentials, own_credentials, NULL))
            authorized = TRUE;
        g_object_unref (own_credentials);
    }
    return authorized;
}