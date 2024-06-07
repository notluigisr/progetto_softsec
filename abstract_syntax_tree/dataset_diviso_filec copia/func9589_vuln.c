static s32 gf_media_vvc_read_pps_bs_internal(GF_BitStream *bs, VVCState *vvc)
{
	u32 i;
	s32 pps_id;
	VVC_PPS *pps;

	
	pps_id = gf_bs_read_int_log(bs, 6, "STR");

	if ((pps_id < 0) || (pps_id >= 64)) {
		GF_LOG(GF_LOG_ERROR, GF_LOG_CODING, ("STR", pps_id));
		return -1;
	}
	pps = &vvc->pps[pps_id];

	if (!pps->state) {
		pps->id = pps_id;
		pps->state = 1;
	}
	pps->sps_id = gf_bs_read_int_log(bs, 4, "STR");
	if (pps->sps_id >= 16) {
		GF_LOG(GF_LOG_ERROR, GF_LOG_CODING, ("STR", pps->sps_id));
		pps->sps_id=0;
		return -1;
	}
	vvc->sps_active_idx = pps->sps_id; 
	pps->mixed_nal_types = gf_bs_read_int_log(bs, 1, "STR");
	pps->width = gf_bs_read_ue_log(bs, "STR");
	pps->height = gf_bs_read_ue_log(bs, "STR");
	pps->conf_window = gf_bs_read_int_log(bs, 1, "STR");
	if (pps->conf_window) {
		pps->cw_left = gf_bs_read_ue_log(bs, "STR");
		pps->cw_right = gf_bs_read_ue_log(bs, "STR");
		pps->cw_top = gf_bs_read_ue_log(bs, "STR");
		pps->cw_bottom = gf_bs_read_ue_log(bs, "STR");
	}
	
	if (gf_bs_read_int_log(bs, 1, "STR")) {
		gf_bs_read_se_log(bs, "STR");
		gf_bs_read_se_log(bs, "STR");
		gf_bs_read_se_log(bs, "STR");
		gf_bs_read_se_log(bs, "STR");
	}
	pps->output_flag_present_flag = gf_bs_read_int_log(bs, 1, "STR");
	pps->no_pic_partition_flag = gf_bs_read_int_log(bs, 1, "STR");
	pps->subpic_id_mapping_present_flag = gf_bs_read_int_log(bs, 1, "STR");
	if (pps->subpic_id_mapping_present_flag) {
		u32 pps_subpic_id_len, pps_num_subpics=0;
		if (!pps->no_pic_partition_flag) {
			pps_num_subpics = 1+gf_bs_read_ue_log(bs, "STR");
		}
		pps_subpic_id_len = 1 + gf_bs_read_ue(bs);
		for (i=0; i<pps_num_subpics; i++) {
			gf_bs_read_int_log_idx(bs, pps_subpic_id_len, "STR", i);
		}
	}
	if (!pps->no_pic_partition_flag) {
		gf_bs_read_int_log(bs, 2, "STR");
		u32 num_exp_tile_columns = 1 + gf_bs_read_ue_log(bs, "STR");
		u32 num_exp_tile_rows = 1 + gf_bs_read_ue_log(bs, "STR");
		for (i=0; i<num_exp_tile_columns; i++)
			gf_bs_read_ue_log_idx(bs, "STR", i);
		for (i=0; i<num_exp_tile_rows; i++)
			gf_bs_read_ue_log_idx(bs, "STR", i);

		
		return pps_id;
	}


	

	return pps_id;
}