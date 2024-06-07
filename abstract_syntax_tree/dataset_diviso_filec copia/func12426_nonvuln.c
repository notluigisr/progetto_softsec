static s32 avc_parse_hrd_parameters(GF_BitStream *bs, AVC_HRD *hrd)
{
	int i, cpb_cnt_minus1;

	cpb_cnt_minus1 = gf_bs_read_ue_log(bs, "STR");
	if (cpb_cnt_minus1 > 31) {
		GF_LOG(GF_LOG_WARNING, GF_LOG_CODING, ("STR", cpb_cnt_minus1));
		return -1;
	}
	gf_bs_read_int_log(bs, 4, "STR");
	gf_bs_read_int_log(bs, 4, "STR");

	
	for (i = 0; i <= cpb_cnt_minus1; i++) {
		gf_bs_read_ue_log_idx(bs, "STR", i);
		gf_bs_read_ue_log_idx(bs, "STR", i);
		gf_bs_read_int_log_idx(bs, 1, "STR", i);
	}
	gf_bs_read_int_log(bs, 5, "STR");
	hrd->cpb_removal_delay_length_minus1 = gf_bs_read_int_log(bs, 5, "STR");
	hrd->dpb_output_delay_length_minus1 = gf_bs_read_int_log(bs, 5, "STR");
	hrd->time_offset_length = gf_bs_read_int_log(bs, 5, "STR");
	return 0;
}