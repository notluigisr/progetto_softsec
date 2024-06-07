void MP4T_OnPacketDone(void *cbk, GF_RTPHeader *header)
{
	u8 disposable;
	GF_RTPHinter *tkHint = (GF_RTPHinter *)cbk;
	if (!tkHint || !tkHint->HintSample) return;
	assert(header->TimeStamp == tkHint->RTPTime);

	disposable = 0;
	if (tkHint->avc_nalu_size) {
		disposable = tkHint->rtp_p->avc_non_idr ? 1 : 0;
	}
	
	else if (tkHint->has_ctts && (tkHint->rtp_p->sl_header.compositionTimeStamp==tkHint->rtp_p->sl_header.decodingTimeStamp)) {
		disposable = 1;
	}

	gf_isom_rtp_packet_set_flags(tkHint->file, tkHint->HintTrack, 0, 0, header->Marker, disposable, 0);
}