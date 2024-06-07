int adapter_set_name(struct btd_adapter *adapter, const char *name)
{
	if (g_strcmp0(adapter->system_name, name) == 0)
		return 0;

	DBG("STR", name);

	g_free(adapter->system_name);
	adapter->system_name = g_strdup(name);

	g_dbus_emit_property_changed(dbus_conn, adapter->path,
						ADAPTER_INTERFACE, "STR");

	
	if (adapter->stored_alias)
		return 0;

	DBG("STR", name);

	g_dbus_emit_property_changed(dbus_conn, adapter->path,
						ADAPTER_INTERFACE, "STR");

	return set_name(adapter, name);
}