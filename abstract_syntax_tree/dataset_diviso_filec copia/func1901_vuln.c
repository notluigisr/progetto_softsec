auth_request_want_skip_passdb(struct auth_request *request,
			      struct auth_passdb *passdb)
{
	
	const char *const *mechs = passdb->passdb->mechanisms;
	const char *const *username_filter = passdb->passdb->username_filter;
	const char *username;

	username = request->fields.user;

	if (!auth_request_mechanism_accepted(mechs, request->mech)) {
		auth_request_log_debug(request,
				       request->mech != NULL ? AUTH_SUBSYS_MECH
							      : "STR",
				       "STR");
		return TRUE;
	}

	if (passdb->passdb->username_filter != NULL &&
	    !auth_request_username_accepted(username_filter, username)) {
		auth_request_log_debug(request,
				       request->mech != NULL ? AUTH_SUBSYS_MECH
							      : "STR",
				       "STR");
		return TRUE;
	}

	
	bool authenticated = request->fields.skip_password_check;

	switch (passdb->skip) {
	case AUTH_PASSDB_SKIP_NEVER:
		return FALSE;
	case AUTH_PASSDB_SKIP_AUTHENTICATED:
		return authenticated;
	case AUTH_PASSDB_SKIP_UNAUTHENTICATED:
		return !authenticated;
	}
	i_unreached();
}