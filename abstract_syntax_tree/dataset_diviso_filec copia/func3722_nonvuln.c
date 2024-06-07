static gboolean property_get_address(const GDBusPropertyTable *property,
					DBusMessageIter *iter, void *user_data)
{
	struct btd_adapter *adapter = user_data;
	char addr[18];
	const char *str = addr;

	ba2str(&adapter->bdaddr, addr);

	dbus_message_iter_append_basic(iter, DBUS_TYPE_STRING, &str);

	return TRUE;
}