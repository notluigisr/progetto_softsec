proxy_C_DigestInit (CK_X_FUNCTION_LIST *self,
                    CK_SESSION_HANDLE handle,
                    CK_MECHANISM_PTR mechanism)
{
	State *state = (State *)self;
	Mapping map;
	CK_RV rv;

	rv = map_session_to_real (state->px, &handle, &map, NULL);
	if (rv != CKR_OK)
		return rv;
	return (map.funcs->C_DigestInit) (handle, mechanism);
}