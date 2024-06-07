static SECURITY_STATUS SEC_ENTRY negotiate_DecryptMessage(PCtxtHandle phContext,
                                                          PSecBufferDesc pMessage,
                                                          ULONG MessageSeqNo, ULONG* pfQOP)
{
	NEGOTIATE_CONTEXT* context = (NEGOTIATE_CONTEXT*)sspi_SecureHandleGetLowerPointer(phContext);

	if (!context)
		return SEC_E_INVALID_HANDLE;

	if (context->mic)
		MessageSeqNo++;

	WINPR_ASSERT(context->mech);
	WINPR_ASSERT(context->mech->pkg);
	WINPR_ASSERT(context->mech->pkg->table);
	if (context->mech->pkg->table->DecryptMessage)
		return context->mech->pkg->table->DecryptMessage(&context->sub_context, pMessage,
		                                                 MessageSeqNo, pfQOP);

	return SEC_E_UNSUPPORTED_FUNCTION;
}