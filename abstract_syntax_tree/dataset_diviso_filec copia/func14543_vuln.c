static UINT drdynvc_process_create_request(drdynvcPlugin* drdynvc, int Sp,
        int cbChId, wStream* s)
{
	size_t pos;
	UINT status;
	UINT32 ChannelId;
	wStream* data_out;
	UINT channel_status;

	if (!drdynvc)
		return CHANNEL_RC_BAD_CHANNEL_HANDLE;

	if (drdynvc->state == DRDYNVC_STATE_CAPABILITIES)
	{
		
		drdynvc->version = 3;

		if ((status = drdynvc_send_capability_response(drdynvc)))
		{
			WLog_Print(drdynvc->log, WLOG_ERROR, "STR");
			return status;
		}

		drdynvc->state = DRDYNVC_STATE_READY;
	}

	ChannelId = drdynvc_read_variable_uint(s, cbChId);
	pos = Stream_GetPosition(s);
	WLog_Print(drdynvc->log, WLOG_DEBUG, "STR",
	           ChannelId,
	           Stream_Pointer(s));
	channel_status = dvcman_create_channel(drdynvc, drdynvc->channel_mgr, ChannelId,
	                                       (char*) Stream_Pointer(s));
	data_out = Stream_New(NULL, pos + 4);

	if (!data_out)
	{
		WLog_Print(drdynvc->log, WLOG_ERROR, "STR");
		return CHANNEL_RC_NO_MEMORY;
	}

	Stream_Write_UINT8(data_out, 0x10 | cbChId);
	Stream_SetPosition(s, 1);
	Stream_Copy(s, data_out, pos - 1);

	if (channel_status == CHANNEL_RC_OK)
	{
		WLog_Print(drdynvc->log, WLOG_DEBUG, "STR");
		Stream_Write_UINT32(data_out, 0);
	}
	else
	{
		WLog_Print(drdynvc->log, WLOG_DEBUG, "STR");
		Stream_Write_UINT32(data_out, (UINT32)0xC0000001); 
	}

	status = drdynvc_send(drdynvc, data_out);

	if (status != CHANNEL_RC_OK)
	{
		WLog_Print(drdynvc->log, WLOG_ERROR, "STR",
		           WTSErrorToString(status), status);
		return status;
	}

	if (channel_status == CHANNEL_RC_OK)
	{
		if ((status = dvcman_open_channel(drdynvc, drdynvc->channel_mgr, ChannelId)))
		{
			WLog_Print(drdynvc->log, WLOG_ERROR, "STR", status);
			return status;
		}
	}
	else
	{
		if ((status = dvcman_close_channel(drdynvc->channel_mgr, ChannelId)))
			WLog_Print(drdynvc->log, WLOG_ERROR, "STR", status);
	}

	return status;
}