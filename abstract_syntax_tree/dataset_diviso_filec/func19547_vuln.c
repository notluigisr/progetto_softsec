static SECURITY_STATUS SEC_ENTRY kerberos_SetCredentialsAttributesX(PCredHandle phCredential,
                                                                    ULONG ulAttribute,
                                                                    void* pBuffer, ULONG cbBuffer,
                                                                    BOOL unicode)
{
#ifdef WITH_GSSAPI
	KRB_CREDENTIALS* credentials;

	if (!phCredential)
		return SEC_E_INVALID_HANDLE;

	credentials = sspi_SecureHandleGetLowerPointer(phCredential);

	if (!credentials)
		return SEC_E_INVALID_HANDLE;

	if (!pBuffer)
		return SEC_E_INSUFFICIENT_MEMORY;

	if (ulAttribute == SECPKG_CRED_ATTR_KDC_URL)
	{
		if (credentials->kdc_url)
		{
			free(credentials->kdc_url);
			credentials->kdc_url = NULL;
		}

		if (unicode)
		{
			SEC_WCHAR* KdcUrl = ((SecPkgCredentials_KdcUrlW*)pBuffer)->KdcUrl;

			if (KdcUrl)
			{
				ConvertFromUnicode(CP_UTF8, 0, (WCHAR*)KdcUrl, -1, &credentials->kdc_url, 0, NULL,
				                   NULL);

				if (!credentials->kdc_url)
					return SEC_E_INSUFFICIENT_MEMORY;
			}
		}
		else
		{
			SEC_CHAR* KdcUrl = ((SecPkgCredentials_KdcUrlA*)pBuffer)->KdcUrl;

			if (KdcUrl)
			{
				credentials->kdc_url = _strdup(KdcUrl);

				if (!credentials->kdc_url)
					return SEC_E_INSUFFICIENT_MEMORY;
			}
		}

		WLog_WARN(TAG, "STR",
		          credentials->kdc_url);
	}

	return SEC_E_UNSUPPORTED_FUNCTION;
#else
	return SEC_E_UNSUPPORTED_FUNCTION;
#endif
}