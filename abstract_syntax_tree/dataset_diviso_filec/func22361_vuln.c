BOOL nego_read_request(rdpNego* nego, wStream* s)
{
	BYTE li;
	BYTE type;
	UINT16 length;

	if (!tpkt_read_header(s, &length))
		return FALSE;

	if (!tpdu_read_connection_request(s, &li, length))
		return FALSE;

	if (li != Stream_GetRemainingLength(s) + 6)
	{
		WLog_ERR(TAG, "STR");
		return FALSE;
	}

	if (!nego_read_request_token_or_cookie(nego, s))
	{
		WLog_ERR(TAG, "STR");
		return FALSE;
	}

	if (Stream_GetRemainingLength(s) >= 8)
	{
		
		Stream_Read_UINT8(s, type); 

		if (type != TYPE_RDP_NEG_REQ)
		{
			WLog_ERR(TAG, "STR", type);
			return FALSE;
		}

		nego_process_negotiation_request(nego, s);
	}

	return tpkt_ensure_stream_consumed(s, length);
}