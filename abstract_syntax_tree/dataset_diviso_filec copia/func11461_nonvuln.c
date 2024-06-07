smtp_transport_get_name (CamelService *service,
                         gboolean brief)
{
	CamelNetworkSettings *network_settings;
	CamelSettings *settings;
	gchar *host;
	gchar *name;

	settings = camel_service_ref_settings (service);

	network_settings = CAMEL_NETWORK_SETTINGS (settings);
	host = camel_network_settings_dup_host (network_settings);

	g_object_unref (settings);

	if (brief)
		name = g_strdup_printf (
			_("STR"), host);
	else
		name = g_strdup_printf (
			_("STR"), host);

	g_free (host);

	return name;
}