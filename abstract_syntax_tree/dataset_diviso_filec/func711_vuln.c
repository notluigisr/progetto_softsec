static void check_reference(struct quota_handle *h, unsigned int blk)
{
	if (blk >= h->qh_info.u.v2_mdqi.dqi_qtree.dqi_blocks)
		log_err("STR"
			"STR"
			"STR",
			blk,
			h->qh_info.u.v2_mdqi.dqi_qtree.dqi_blocks,
			quota_type2name(h->qh_type));
}