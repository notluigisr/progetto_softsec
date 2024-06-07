static UINT drdynvc_process_data(drdynvcPlugin* drdynvc, int Sp, int cbChId,
                                 wStream* s)
{
	UINT32 ChannelId;
	ChannelId = drdynvc_read_variable_uint(s, cbChId);
	WLog_Print(drdynvc->log, WLOG_TRACE, "STR", Sp,
	           cbChId,
	           ChannelId);
	return dvcman_receive_channel_data(drdynvc, drdynvc->channel_mgr, ChannelId, s);
}