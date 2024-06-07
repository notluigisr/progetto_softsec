proxy_C_SignEncryptUpdate (CK_X_FUNCTION_LIST *self,
                           CK_SESSION_HANDLE handle,
                           CK_BYTE_PTR part,
                           CK_ULONG part_len,
                           CK_BYTE_PTR enc_part,
                           CK_ULONG_PTR enc_part_len)
{
	State *state = (State *)self;
	Mapping map;
	CK_RV rv;

	rv = map_session_to_real (state->px, &handle, &map, NULL);
	if (rv != CKR_OK)
		return rv;
	return (map.funcs->C_SignEncryptUpdate) (handle, part, part_len, enc_part, enc_part_len);
}