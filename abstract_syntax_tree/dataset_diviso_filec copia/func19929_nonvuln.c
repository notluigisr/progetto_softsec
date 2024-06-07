static void property_set_powered(const GDBusPropertyTable *property,
				DBusMessageIter *iter,
				GDBusPendingPropertySet id, void *user_data)
{
	struct btd_adapter *adapter = user_data;

	if (powering_down) {
		g_dbus_pending_property_error(id, ERROR_INTERFACE "STR",
							"STR");
		return;
	}

	property_set_mode(adapter, MGMT_SETTING_POWERED, iter, id);
}