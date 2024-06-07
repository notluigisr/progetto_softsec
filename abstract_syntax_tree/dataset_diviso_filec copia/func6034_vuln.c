s32 vvc_parse_picture_header(GF_BitStream *bs, VVCState *vvc, VVCSliceInfo *si)
{
	u32 pps_id;

	si->irap_or_gdr_pic = gf_bs_read_int_log(bs, 1, "STR");
	si->non_ref_pic = gf_bs_read_int_log(bs, 1, "STR");
	if (si->irap_or_gdr_pic)
		si->gdr_pic = gf_bs_read_int_log(bs, 1, "STR");
	if ((si->inter_slice_allowed_flag = gf_bs_read_int_log(bs, 1, "STR")))
		si->intra_slice_allowed_flag = gf_bs_read_int_log(bs, 1, "STR");

	pps_id = gf_bs_read_ue_log(bs, "STR");
	if (pps_id >= 64)
		return -1;
	si->pps = &vvc->pps[pps_id];
	si->sps = &vvc->sps[si->pps->sps_id];
	si->poc_lsb = gf_bs_read_int_log(bs, si->sps->log2_max_poc_lsb, "STR");

	si->recovery_point_valid = 0;
	si->gdr_recovery_count = 0;
	if (si->gdr_pic) {
		si->recovery_point_valid = 1;
		si->gdr_recovery_count = gf_bs_read_ue_log(bs, "STR");
	}
	gf_bs_read_int_log(bs, si->sps->ph_num_extra_bits, "STR");

	if (si->sps->poc_msb_cycle_flag) {
		if ( (si->poc_msb_cycle_present_flag = gf_bs_read_int_log(bs, 1, "STR"))) {
			si->poc_msb_cycle = gf_bs_read_int_log(bs, si->sps->poc_msb_cycle_len, "STR");
		}
	}

	return 0;
}