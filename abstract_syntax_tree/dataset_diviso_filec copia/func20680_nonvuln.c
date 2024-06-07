void auth_request_default_verify_plain_continue(struct auth_request *request,
						verify_plain_callback_t *callback)
{
	struct auth_passdb *passdb;
	enum passdb_result result;
	const char *cache_key, *error;
	const char *password = request->mech_password;

	i_assert(request->state == AUTH_REQUEST_STATE_MECH_CONTINUE);

	if (auth_request_is_disabled_master_user(request)) {
		callback(PASSDB_RESULT_USER_UNKNOWN, request);
		return;
	}

	if (password_has_illegal_chars(password)) {
		e_info(authdb_event(request),
		       "STR");
		callback(PASSDB_RESULT_USER_UNKNOWN, request);
		return;
	}

	passdb = request->passdb;

	while (passdb != NULL && auth_request_want_skip_passdb(request, passdb))
		passdb = passdb->next;

	request->passdb = passdb;

	if (passdb == NULL) {
		auth_request_log_error(request,
			request->mech != NULL ? AUTH_SUBSYS_MECH : "STR",
			"STR");
		callback(PASSDB_RESULT_INTERNAL_FAILURE, request);
		return;
	}

	auth_request_passdb_lookup_begin(request);
	request->private_callback.verify_plain = callback;

	cache_key = passdb_cache == NULL ? NULL : passdb->cache_key;
	if (passdb_cache_verify_plain(request, cache_key, password,
				      &result, FALSE)) {
		return;
	}

	auth_request_set_state(request, AUTH_REQUEST_STATE_PASSDB);
	
	request->wanted_credentials_scheme = NULL;

	if (passdb->passdb->iface.verify_plain == NULL) {
		
		auth_request_verify_plain_callback(
			PASSDB_RESULT_INTERNAL_FAILURE, request);
	} else if (passdb->passdb->blocking) {
		passdb_blocking_verify_plain(request);
	} else if (passdb_template_export(passdb->default_fields_tmpl,
					  request, &error) < 0) {
		e_error(authdb_event(request),
			"STR", error);
		auth_request_verify_plain_callback(
			PASSDB_RESULT_INTERNAL_FAILURE, request);
	} else {
		passdb->passdb->iface.verify_plain(request, password,
					   auth_request_verify_plain_callback);
	}
}