static void writegen_write_wav_header(GF_GenDumpCtx *ctx)
{
	u32 size;
	u8 *output;
	GF_FilterPacket *dst_pck;
	const GF_PropertyValue *p;
	u32 nb_ch, sample_rate, afmt, bps;
	const char chunkID[] = {'R', 'I', 'F', 'F'};
	const char format[] = {'W', 'A', 'V', 'E'};
	const char subchunk1ID[] = {'f', 'm', 't', ' '};
	const char subchunk2ID[] = {'d', 'a', 't', 'a'};

	if (ctx->is_wav!=1) return;
	ctx->is_wav = 2;

	p = gf_filter_pid_get_property(ctx->ipid, GF_PROP_PID_SAMPLE_RATE);
	if (!p) return;
	sample_rate = p->value.uint;
	p = gf_filter_pid_get_property(ctx->ipid, GF_PROP_PID_NUM_CHANNELS);
	if (!p) return;
	nb_ch = p->value.uint;
	p = gf_filter_pid_get_property(ctx->ipid, GF_PROP_PID_AUDIO_FORMAT);
	if (!p) return;
	afmt = p->value.uint;

	bps = gf_audio_fmt_bit_depth(afmt);

	size = 44;
	dst_pck = gf_filter_pck_new_alloc(ctx->opid, size, &output);
	if (!dst_pck) return;

	if (!ctx->bs) ctx->bs = gf_bs_new(output, size, GF_BITSTREAM_WRITE);
	else gf_bs_reassign_buffer(ctx->bs, output, size);

	gf_bs_write_data(ctx->bs, chunkID, 4);
	gf_bs_write_u32_le(ctx->bs, (u32) ctx->nb_bytes + 36);
	gf_bs_write_data(ctx->bs, format, 4);

	gf_bs_write_data(ctx->bs, subchunk1ID, 4);
	gf_bs_write_u32_le(ctx->bs, 16); 
	gf_bs_write_u16_le(ctx->bs, 1); 
	gf_bs_write_u16_le(ctx->bs, nb_ch);
	gf_bs_write_u32_le(ctx->bs, sample_rate);
	gf_bs_write_u32_le(ctx->bs, sample_rate * nb_ch * bps / 8); 
	gf_bs_write_u16_le(ctx->bs, nb_ch * bps / 8); 
	gf_bs_write_u16_le(ctx->bs, bps);

	gf_bs_write_data(ctx->bs, subchunk2ID, 4);
	gf_bs_write_u32_le(ctx->bs, (u32) ctx->nb_bytes);

	gf_filter_pck_set_framing(dst_pck, GF_FALSE, GF_FALSE);
	gf_filter_pck_set_byte_offset(dst_pck, 0);
	gf_filter_pck_set_seek_flag(dst_pck, GF_TRUE);
	gf_filter_pck_send(dst_pck);
}