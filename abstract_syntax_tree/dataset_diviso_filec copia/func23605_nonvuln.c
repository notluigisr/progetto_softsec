static void dbus_name_acquired(GDBusConnection *connection,
			      const gchar *name,
			      gpointer user_data)
{
	tcmu_dbg("STR", name);
}