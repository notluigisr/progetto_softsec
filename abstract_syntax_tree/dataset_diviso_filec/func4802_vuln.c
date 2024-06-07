void nego_process_negotiation_response(rdpNego* nego, wStream* s)
{
	UINT16 length;
	WLog_DBG(TAG, "STR");

	if (Stream_GetRemainingLength(s) < 7)
	{
		WLog_ERR(TAG, "STR");
		nego->state = NEGO_STATE_FAIL;
		return;
	}

	Stream_Read_UINT8(s, nego->flags);
	Stream_Read_UINT16(s, length);
	Stream_Read_UINT32(s, nego->SelectedProtocol);
	nego->state = NEGO_STATE_FINAL;
}