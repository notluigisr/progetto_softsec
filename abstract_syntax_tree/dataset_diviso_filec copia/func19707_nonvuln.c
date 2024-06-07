static UINT rdpei_recv_pdu(RDPEI_CHANNEL_CALLBACK* callback, wStream* s)
{
	UINT16 eventId;
	UINT32 pduLength;
	UINT error;
	if (Stream_GetRemainingLength(s) < 6)
		return ERROR_INVALID_DATA;

	Stream_Read_UINT16(s, eventId);   
	Stream_Read_UINT32(s, pduLength); 
#ifdef WITH_DEBUG_RDPEI
	WLog_DBG(TAG, "STR", eventId,
	         rdpei_eventid_string(eventId), pduLength);
#endif

	switch (eventId)
	{
		case EVENTID_SC_READY:
			if ((error = rdpei_recv_sc_ready_pdu(callback, s)))
			{
				WLog_ERR(TAG, "STR", error);
				return error;
			}

			if ((error = rdpei_send_cs_ready_pdu(callback)))
			{
				WLog_ERR(TAG, "STR", error);
				return error;
			}

			break;

		case EVENTID_SUSPEND_TOUCH:
			if ((error = rdpei_recv_suspend_touch_pdu(callback, s)))
			{
				WLog_ERR(TAG, "STR", error);
				return error;
			}

			break;

		case EVENTID_RESUME_TOUCH:
			if ((error = rdpei_recv_resume_touch_pdu(callback, s)))
			{
				WLog_ERR(TAG, "STR", error);
				return error;
			}

			break;

		default:
			break;
	}

	return CHANNEL_RC_OK;
}