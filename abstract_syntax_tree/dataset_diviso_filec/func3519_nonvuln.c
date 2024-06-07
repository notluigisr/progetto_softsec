wStream* rdp_message_channel_pdu_init(rdpRdp* rdp)
{
	wStream* s = transport_send_stream_init(rdp->transport, 4096);

	if (!s)
		return NULL;

	if (!Stream_SafeSeek(s, RDP_PACKET_HEADER_MAX_LENGTH))
		goto fail;

	if (!rdp_security_stream_init(rdp, s, TRUE))
		goto fail;

	return s;
fail:
	Stream_Release(s);
	return NULL;
}