static SECURITY_STATUS SEC_ENTRY negotiate_SetCredentialsAttributesW(PCredHandle phCredential,
                                                                     ULONG ulAttribute,
                                                                     void* pBuffer, ULONG cbBuffer)
{
	MechCred* creds;

	creds = sspi_SecureHandleGetLowerPointer(phCredential);

	if (!creds)
		return SEC_E_INVALID_HANDLE;

	for (size_t i = 0; i < MECH_COUNT; i++)
	{
		MechCred* cred = &creds[i];

		if (!cred->valid)
			continue;

		WINPR_ASSERT(cred->mech);
		WINPR_ASSERT(cred->mech->pkg);
		WINPR_ASSERT(cred->mech->pkg->table);
		WINPR_ASSERT(cred->mech->pkg->table_w->SetCredentialsAttributesW);
		cred->mech->pkg->table_w->SetCredentialsAttributesW(&cred->cred, ulAttribute, pBuffer,
		                                                    cbBuffer);
	}

	return SEC_E_OK;
}