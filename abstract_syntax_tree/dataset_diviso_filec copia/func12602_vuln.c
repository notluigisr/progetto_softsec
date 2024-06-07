static int input_init(void)
{
	GKeyFile *config;
	GError *err = NULL;

	config = load_config_file(CONFIGDIR "STR");
	if (config) {
		int idle_timeout;
		gboolean uhid_enabled;

		idle_timeout = g_key_file_get_integer(config, "STR",
							"STR", &err);
		if (!err) {
			DBG("STR", idle_timeout);
			input_set_idle_timeout(idle_timeout * 60);
		} else
			g_clear_error(&err);

		uhid_enabled = g_key_file_get_boolean(config, "STR",
							"STR", &err);
		if (!err) {
			DBG("STR", uhid_enabled ?
							"STR");
			input_enable_userspace_hid(uhid_enabled);
		} else
			g_clear_error(&err);
	}

	btd_profile_register(&input_profile);

	if (config)
		g_key_file_free(config);

	return 0;
}