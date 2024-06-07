static u32 merge_avc_config(GF_ISOFile *dest, u32 tk_id, GF_ISOFile **o_orig, u32 src_track, Bool force_cat, u32 *orig_nal_len, u32 *dst_nal_len)
{
	GF_AVCConfig *avc_src, *avc_dst;
	GF_ISOFile *orig = *o_orig;
	u32 dst_tk = gf_isom_get_track_by_id(dest, tk_id);

	avc_src = gf_isom_avc_config_get(orig, src_track, 1);
	avc_dst = gf_isom_avc_config_get(dest, dst_tk, 1);

	if (!force_cat && (avc_src->AVCLevelIndication!=avc_dst->AVCLevelIndication)) {
		dst_tk = 0;
	} else if (!force_cat && (avc_src->AVCProfileIndication!=avc_dst->AVCProfileIndication)) {
		dst_tk = 0;
	}
	else {
		
		if (avc_src->nal_unit_size > avc_dst->nal_unit_size) {
			gf_media_nal_rewrite_samples(dest, dst_tk, 8*avc_src->nal_unit_size);
			avc_dst->nal_unit_size = avc_src->nal_unit_size;
		} else if (avc_src->nal_unit_size < avc_dst->nal_unit_size) {
			*orig_nal_len = avc_src->nal_unit_size;
			*dst_nal_len = avc_dst->nal_unit_size;
		}

		
		if (!merge_parameter_set(avc_src->sequenceParameterSets, avc_dst->sequenceParameterSets, "STR"))
			dst_tk = 0;
		if (!merge_parameter_set(avc_src->pictureParameterSets, avc_dst->pictureParameterSets, "STR"))
			dst_tk = 0;

		gf_isom_avc_config_update(dest, dst_tk, 1, avc_dst);
	}

	gf_odf_avc_cfg_del(avc_src);
	gf_odf_avc_cfg_del(avc_dst);

	if (!dst_tk) {
		dst_tk = gf_isom_get_track_by_id(dest, tk_id);
		gf_isom_set_nalu_extract_mode(orig, src_track, GF_ISOM_NALU_EXTRACT_INBAND_PS_FLAG);
		if (!force_cat) {
			gf_isom_avc_set_inband_config(dest, dst_tk, 1, GF_FALSE);
		} else {
			M4_LOG(GF_LOG_WARNING, ("STR", tk_id));
		}
	}
	return dst_tk;
}