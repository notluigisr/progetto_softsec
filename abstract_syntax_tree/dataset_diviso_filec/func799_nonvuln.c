SpoolssRRPCN_q(tvbuff_t *tvb, int offset, packet_info *pinfo,
			  proto_tree *tree, dcerpc_info *di, guint8 *drep)
{
	guint32 changeid;

	

	offset = dissect_nt_policy_hnd(
		tvb, offset, pinfo, tree, di, drep, hf_hnd, NULL, NULL,
		FALSE, FALSE);

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, tree, di, drep, hf_rrpcn_changelow, &changeid);

	col_append_fstr(
			pinfo->cinfo, COL_INFO, "STR", changeid);

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, tree, di, drep, hf_rrpcn_changehigh, NULL);

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, tree, di, drep, hf_rrpcn_unk0, NULL);

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, tree, di, drep, hf_rrpcn_unk1, NULL);

	offset = dissect_ndr_pointer(
		tvb, offset, pinfo, tree, di, drep,
		dissect_NOTIFY_INFO, NDR_POINTER_UNIQUE,
		"STR", -1);

	

	return offset;
}