static void xcopy_pt_undepend_remotedev(struct xcopy_op *xop)
{
	struct se_device *remote_dev;

	if (xop->op_origin == XCOL_SOURCE_RECV_OP)
		remote_dev = xop->dst_dev;
	else
		remote_dev = xop->src_dev;

	pr_debug("STR"
		  "STR",
		  remote_dev, &remote_dev->dev_group.cg_item);

	target_undepend_item(&remote_dev->dev_group.cg_item);
}