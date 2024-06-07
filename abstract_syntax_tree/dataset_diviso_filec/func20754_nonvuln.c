gdm_session_settings_get_session_name (GdmSessionSettings *settings)
{
        g_return_val_if_fail (GDM_IS_SESSION_SETTINGS (settings), NULL);
        return g_strdup (settings->priv->session_name);
}