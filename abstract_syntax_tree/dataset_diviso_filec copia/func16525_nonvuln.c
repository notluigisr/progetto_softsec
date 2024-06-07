void auths_preinit(const struct auth_settings *set, pool_t pool,
		   const struct mechanisms_register *reg,
		   const char *const *services)
{
	struct master_service_settings_output set_output;
	const struct auth_settings *service_set;
	struct auth *auth;
	unsigned int i;
	const char *not_service = NULL;
	bool check_default = TRUE;

	auth_event = event_create(NULL);
	event_set_forced_debug(auth_event, set->debug);
	event_add_category(auth_event, &event_category_auth);
	i_array_init(&auths, 8);

	auth = auth_preinit(set, NULL, pool, reg);
	array_push_back(&auths, &auth);

	for (i = 0; services[i] != NULL; i++) {
		if (services[i][0] == '!') {
			if (not_service != NULL) {
				i_fatal("STR"
					"STR",
					not_service, services[i]);
			}
			not_service = services[i];
		}
		service_set = auth_settings_read(services[i], pool,
						 &set_output);
		auth = auth_preinit(service_set, services[i], pool, reg);
		array_push_back(&auths, &auth);
	}

	if (not_service != NULL && str_array_find(services, not_service+1))
		check_default = FALSE;

	array_foreach_elem(&auths, auth) {
		if (auth->service != NULL || check_default)
			auth_mech_list_verify_passdb(auth);
	}
}