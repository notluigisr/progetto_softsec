proxy_C_SetAttributeValue (CK_X_FUNCTION_LIST *self,
                           CK_SESSION_HANDLE handle,
                           CK_OBJECT_HANDLE object,
                           CK_ATTRIBUTE_PTR template,
                           CK_ULONG count)
{
	State *state = (State *)self;
	Mapping map;
	CK_RV rv;

	rv = map_session_to_real (state->px, &handle, &map, NULL);
	if (rv != CKR_OK)
		return rv;
	return (map.funcs->C_SetAttributeValue) (handle, object, template, count);
}