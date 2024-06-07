wStream* rdp_data_pdu_init(rdpRdp* rdp)
{
	wStream* s = rdp_send_stream_pdu_init(rdp);

	if (!s)
		return NULL;

	if (!Stream_SafeSeek(s, RDP_SHARE_DATA_HEADER_LENGTH))
		goto fail;

	return s;
fail:
	Stream_Release(s);
	return NULL;
}