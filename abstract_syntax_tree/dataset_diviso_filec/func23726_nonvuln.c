nma_gconf_connection_new_from_connection (GConfClient *client,
								  const char *conf_dir,
								  NMConnection *connection)
{
	g_return_val_if_fail (GCONF_IS_CLIENT (client), NULL);
	g_return_val_if_fail (conf_dir != NULL, NULL);
	g_return_val_if_fail (NM_IS_CONNECTION (connection), NULL);

	return (NMAGConfConnection *) g_object_new (NMA_TYPE_GCONF_CONNECTION,
									    NMA_GCONF_CONNECTION_CLIENT, client,
									    NMA_GCONF_CONNECTION_DIR, conf_dir,
									    NM_EXPORTED_CONNECTION_CONNECTION, connection,
									    NULL);
}