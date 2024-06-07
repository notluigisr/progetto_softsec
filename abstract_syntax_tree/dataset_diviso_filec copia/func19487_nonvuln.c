read_one_cert (ReadFromGConfInfo *info,
               const char *setting_name,
               const char *key,
               gboolean fail_if_missing,
               GError **error)
{
	char *value = NULL;

	if (nm_gconf_get_string_helper (info->client, info->dir, key, setting_name, &value)) {
		if (fail_if_missing && !g_file_test (value, G_FILE_TEST_EXISTS)) {
			g_set_error (error, 0, 0, _("STR"), value);
			return FALSE;
		}

		g_object_set_data_full (G_OBJECT (info->connection), key, value, (GDestroyNotify) g_free);
	}
	return TRUE;
}