gs_window_cancel_unlock_request (GSWindow  *window)
{
        
        g_return_if_fail (GS_IS_WINDOW (window));

        if (window->priv->lock_socket == NULL) {
                return;
        }

        if (window->priv->lock_pid > 0) {
                kill (window->priv->lock_pid, SIGTERM);
        }
}