gs_window_set_status_message (GSWindow   *window,
                            const char *status_message)
{
        g_return_if_fail (GS_IS_WINDOW (window));

        g_free (window->priv->status_message);
        window->priv->status_message = g_strdup (status_message);
}