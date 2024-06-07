static bool auth_request_is_disabled_master_user(struct auth_request *request)
{
	if (request->fields.requested_login_user == NULL ||
	    request->passdb != NULL)
		return FALSE;

	
	e_info(request->mech_event,
	       "STR"
	       "STR",
	       request->fields.requested_login_user);
	return TRUE;
}