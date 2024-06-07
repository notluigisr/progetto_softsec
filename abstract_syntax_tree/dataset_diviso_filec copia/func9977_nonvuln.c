rpc_C_DigestUpdate (CK_X_FUNCTION_LIST *self,
                    p11_rpc_message *msg)
{
	CK_SESSION_HANDLE session;
	CK_BYTE_PTR part;
	CK_ULONG part_len;

	BEGIN_CALL (DigestUpdate);
		IN_ULONG (session);
		IN_BYTE_ARRAY (part, part_len);
	PROCESS_CALL ((self, session, part, part_len));
	END_CALL;
}