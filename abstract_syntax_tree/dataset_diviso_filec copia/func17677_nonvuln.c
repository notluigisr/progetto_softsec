nma_gconf_settings_init (NMAGConfSettings *settings)
{
	NMAGConfSettingsPrivate *priv = NMA_GCONF_SETTINGS_GET_PRIVATE (settings);

	priv->client = gconf_client_get_default ();
	priv->pending_changes = g_hash_table_new_full (g_str_hash, g_str_equal, NULL, remove_pending_change);

	gconf_client_add_dir (priv->client,
	                      GCONF_PATH_CONNECTIONS,
	                      GCONF_CLIENT_PRELOAD_NONE,
	                      NULL);

	priv->conf_notify_id = gconf_client_notify_add (priv->client,
										   GCONF_PATH_CONNECTIONS,
										   (GConfClientNotifyFunc) connections_changed_cb,
										   settings,
										   NULL, NULL);
}