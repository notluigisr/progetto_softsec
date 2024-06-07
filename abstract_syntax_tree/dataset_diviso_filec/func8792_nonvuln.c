void btd_gatt_database_destroy(struct btd_gatt_database *database)
{
	if (!database)
		return;

	g_dbus_unregister_interface(btd_get_dbus_connection(),
					adapter_get_path(database->adapter),
					GATT_MANAGER_IFACE);

	gatt_database_free(database);
}