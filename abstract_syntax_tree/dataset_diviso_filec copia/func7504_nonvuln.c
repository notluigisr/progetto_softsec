void latm_flush(GP_RTPPacketizer *builder)
{
	if (builder->bytesInPacket) {
		builder->OnPacketDone(builder->cbk_obj, &builder->rtp_header);
		builder->bytesInPacket = 0;
	}
	builder->rtp_header.TimeStamp = (u32) builder->sl_header.compositionTimeStamp;
}