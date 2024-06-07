void nego_process_negotiation_failure(rdpNego* nego, wStream* s)
{
	BYTE flags;
	UINT16 length;
	UINT32 failureCode;
	WLog_DBG(TAG, "STR");
	Stream_Read_UINT8(s, flags);
	Stream_Read_UINT16(s, length);
	Stream_Read_UINT32(s, failureCode);

	switch (failureCode)
	{
		case SSL_REQUIRED_BY_SERVER:
			WLog_WARN(TAG, "STR");
			break;

		case SSL_NOT_ALLOWED_BY_SERVER:
			WLog_WARN(TAG, "STR");
			nego->sendNegoData = TRUE;
			break;

		case SSL_CERT_NOT_ON_SERVER:
			WLog_ERR(TAG, "STR");
			nego->sendNegoData = TRUE;
			break;

		case INCONSISTENT_FLAGS:
			WLog_ERR(TAG, "STR");
			break;

		case HYBRID_REQUIRED_BY_SERVER:
			WLog_WARN(TAG, "STR");
			break;

		default:
			WLog_ERR(TAG, "STR", failureCode);
			break;
	}

	nego->state = NEGO_STATE_FAIL;
}