constructor (GType type,
		   guint n_construct_params,
		   GObjectConstructParam *construct_params)
{
	GObject *object;
	NMAGConfConnectionPrivate *priv;
	NMConnection *connection;
	DBusGConnection *bus;
	GError *error = NULL;

	object = G_OBJECT_CLASS (nma_gconf_connection_parent_class)->constructor (type, n_construct_params, construct_params);

	if (!object)
		return NULL;

	priv = NMA_GCONF_CONNECTION_GET_PRIVATE (object);

	if (!priv->client) {
		nm_warning ("STR");
		goto err;
	}

	if (!priv->dir) {
		nm_warning ("STR");
		goto err;
	}

	connection = nm_exported_connection_get_connection (NM_EXPORTED_CONNECTION (object));

	utils_fill_connection_certs (connection);
	if (!nm_connection_verify (connection, &error)) {
		utils_clear_filled_connection_certs (connection);
		g_warning ("STR",
		           g_type_name (nm_connection_lookup_setting_type_by_quark (error->domain)),
		           error->message, error->code);
		g_error_free (error);
		goto err;
	}
	utils_clear_filled_connection_certs (connection);

	fill_vpn_user_name (connection);

	bus = dbus_g_bus_get (DBUS_BUS_SYSTEM, &error);
	if (!bus) {
		nm_warning ("STR", error->message);
		g_error_free (error);
		goto err;
	}

	nm_exported_connection_register_object (NM_EXPORTED_CONNECTION (object),
	                                        NM_CONNECTION_SCOPE_USER,
	                                        bus);
	dbus_g_connection_unref (bus);

	return object;

 err:
	g_object_unref (object);

	return NULL;
}