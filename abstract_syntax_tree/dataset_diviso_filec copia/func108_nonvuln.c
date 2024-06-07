handle_get_property(__attribute__((unused)) GDBusConnection *connection,
		    __attribute__((unused)) const gchar     *sender,
					    const gchar     *object_path,
					    const gchar     *interface_name,
					    const gchar     *property_name,
					    GError	   **error,
		    __attribute__((unused)) gpointer	     user_data)
{
	GVariant *ret = NULL;
	dbus_queue_ent_t ent;
	char ifname_str[sizeof ((vrrp_t*)NULL)->ifp->ifname];
	int action;

	if (g_strcmp0(interface_name, DBUS_VRRP_INSTANCE_INTERFACE)) {
		log_message(LOG_INFO, "STR", interface_name);
		return NULL;
	}

	if (!g_strcmp0(property_name, "STR"))
		action = DBUS_GET_NAME;
	else if (!g_strcmp0(property_name, "STR"))
		action = DBUS_GET_STATUS;
	else {
		log_message(LOG_INFO, "STR", property_name);
		return NULL;
	}

	get_interface_ids(object_path, ifname_str, &ent.vrid, &ent.family);

	ent.action = action;
	ent.ifname = ifname_str;
	ent.args = NULL;
	process_method_call(&ent);
	if (ent.reply == DBUS_SUCCESS)
		ret = ent.args;
	else
		g_set_error(error, G_DBUS_ERROR, G_DBUS_ERROR_INVALID_ARGS, "STR", ifname_str, ent.vrid, family_str(ent.family));

	return ret;
}