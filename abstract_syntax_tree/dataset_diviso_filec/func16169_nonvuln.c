proxy_C_CreateObject (CK_X_FUNCTION_LIST *self,
                      CK_SESSION_HANDLE handle,
                      CK_ATTRIBUTE_PTR template,
                      CK_ULONG count,
                      CK_OBJECT_HANDLE_PTR new_object)
{
	State *state = (State *)self;
	Mapping map;
	CK_RV rv;

	rv = map_session_to_real (state->px, &handle, &map, NULL);
	if (rv != CKR_OK)
		return rv;

	return (map.funcs->C_CreateObject) (handle, template, count, new_object);
}