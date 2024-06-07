utils_filter_connections_for_device (NMDevice *device, GSList *connections)
{
	GSList *iter;
	GSList *filtered = NULL;

	for (iter = connections; iter; iter = g_slist_next (iter)) {
		NMConnection *connection = NM_CONNECTION (iter->data);

		if (utils_connection_valid_for_device (connection, device, NULL))
			filtered = g_slist_append (filtered, connection);
	}

	return filtered;
}