static UINT drdynvc_process_capability_request(drdynvcPlugin* drdynvc, int Sp,
        int cbChId, wStream* s)
{
	UINT status;

	if (!drdynvc)
		return CHANNEL_RC_BAD_INIT_HANDLE;

	WLog_Print(drdynvc->log, WLOG_TRACE, "STR", Sp, cbChId);
	Stream_Seek(s, 1); 
	Stream_Read_UINT16(s, drdynvc->version);

	
	if ((drdynvc->version == 2) || (drdynvc->version == 3))
	{
		Stream_Read_UINT16(s, drdynvc->PriorityCharge0);
		Stream_Read_UINT16(s, drdynvc->PriorityCharge1);
		Stream_Read_UINT16(s, drdynvc->PriorityCharge2);
		Stream_Read_UINT16(s, drdynvc->PriorityCharge3);
	}

	status = drdynvc_send_capability_response(drdynvc);
	drdynvc->state = DRDYNVC_STATE_READY;
	return status;
}