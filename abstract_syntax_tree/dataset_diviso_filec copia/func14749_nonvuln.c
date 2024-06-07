auth_request_want_skip_userdb(struct auth_request *request,
			      struct auth_userdb *userdb)
{
	switch (userdb->skip) {
	case AUTH_USERDB_SKIP_NEVER:
		return FALSE;
	case AUTH_USERDB_SKIP_FOUND:
		return request->userdb_success;
	case AUTH_USERDB_SKIP_NOTFOUND:
		return !request->userdb_success;
	}
	i_unreached();
}