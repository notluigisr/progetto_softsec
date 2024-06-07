static errcode_t quota_read_all_dquots(struct quota_handle *qh,
                                       quota_ctx_t qctx,
				       int update_limits EXT2FS_ATTR((unused)))
{
	struct scan_dquots_data scan_data;

	scan_data.quota_dict = qctx->quota_dict[qh->qh_type];
	scan_data.check_consistency = 0;
	scan_data.update_limits = 0;
	scan_data.update_usage = 1;

	return qh->qh_ops->scan_dquots(qh, scan_dquots_callback, &scan_data);
}