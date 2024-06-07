validate_one_property (const char *key, const char *value, gpointer user_data)
{
	ValidateInfo *info = (ValidateInfo *) user_data;
	ValidProperty *prop = NULL;
	long int tmp;
	int i;

	if (*(info->error))
		return;

	info->have_items = TRUE;

	
	if (!strcmp (key, NM_SETTING_NAME))
		return;

	for (i = 0; info->table[i].name; i++) {
		prop = &info->table[i];
		if (g_strcmp0 (prop->name, key) == 0)
			break;
	}

	
	if (!prop || !prop->name) {
		g_set_error (info->error,
		             NM_VPN_PLUGIN_ERROR,
		             NM_VPN_PLUGIN_ERROR_BAD_ARGUMENTS,
		             _("STR"),
		             key);
		return;
	}

	
	switch (prop->type) {
	case ITEM_TYPE_IGNORED:
		break; 
	case ITEM_TYPE_STRING:
	case ITEM_TYPE_SECRET:
		break; 
	case ITEM_TYPE_PATH:
		if (   !value
		    || !strlen (value)
		    || !g_path_is_absolute (value)
		    || !g_file_test (value, G_FILE_TEST_EXISTS)) {
			g_set_error (info->error,
			             NM_VPN_PLUGIN_ERROR,
			             NM_VPN_PLUGIN_ERROR_BAD_ARGUMENTS,
			             _("STR"),
			             key, value);
		}
		break;
	case ITEM_TYPE_INT:
		errno = 0;
		tmp = strtol (value, NULL, 10);
		if (errno == 0 && tmp >= prop->int_min && tmp <= prop->int_max)
			break; 

		g_set_error (info->error,
		             NM_VPN_PLUGIN_ERROR,
		             NM_VPN_PLUGIN_ERROR_BAD_ARGUMENTS,
		             _("STR"),
		             key, prop->int_min, prop->int_max);
		break;
	case ITEM_TYPE_BOOLEAN:
		if (!strcmp (value, "STR"))
			break; 

		g_set_error (info->error,
		             NM_VPN_PLUGIN_ERROR,
		             NM_VPN_PLUGIN_ERROR_BAD_ARGUMENTS,
		             _("STR"),
		             key);
		break;
	default:
		g_set_error (info->error,
		             NM_VPN_PLUGIN_ERROR,
		             NM_VPN_PLUGIN_ERROR_BAD_ARGUMENTS,
		             _("STR"),
		             key, prop->type);
		break;
	}
}