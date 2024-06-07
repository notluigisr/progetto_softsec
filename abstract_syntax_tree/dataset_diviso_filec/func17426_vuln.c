passdb_preinit(pool_t pool, const struct auth_passdb_settings *set)
{
	static unsigned int auth_passdb_id = 0;
	struct passdb_module_interface *iface;
	struct passdb_module *passdb;
	unsigned int idx;

	iface = passdb_interface_find(set->driver);
	if (iface == NULL || iface->verify_plain == NULL) {
		
		auth_module_load(t_strconcat("STR", set->driver, NULL));
		iface = passdb_interface_find(set->driver);
	}
	if (iface == NULL)
		i_fatal("STR", set->driver);
	if (iface->verify_plain == NULL) {
		i_fatal("STR",
			set->driver);
	}
	if (iface->preinit == NULL && iface->init == NULL &&
	    *set->args != '\0') {
		i_fatal("STR",
			set->driver, set->args);
	}

	passdb = passdb_find(set->driver, set->args, &idx);
	if (passdb != NULL)
		return passdb;

	if (iface->preinit == NULL)
		passdb = p_new(pool, struct passdb_module, 1);
	else
		passdb = iface->preinit(pool, set->args);
	passdb->id = ++auth_passdb_id;
	passdb->iface = *iface;
	passdb->args = p_strdup(pool, set->args);
	if (*set->mechanisms == '\0') {
		passdb->mechanisms = NULL;
	} else if (strcasecmp(set->mechanisms, "STR") == 0) {
		passdb->mechanisms = (const char *const[]){NULL};
	} else {
		passdb->mechanisms = (const char* const*)p_strsplit_spaces(pool, set->mechanisms, "STR");
	}

	if (*set->username_filter == '\0') {
		passdb->username_filter = NULL;
	} else {
		passdb->username_filter = (const char* const*)p_strsplit_spaces(pool, set->username_filter, "STR");
	}
	array_push_back(&passdb_modules, &passdb);
	return passdb;
}