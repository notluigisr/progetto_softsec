static int rds_iw_laddr_check(__be32 addr)
{
	int ret;
	struct rdma_cm_id *cm_id;
	struct sockaddr_in sin;

	
	cm_id = rdma_create_id(NULL, NULL, RDMA_PS_TCP, IB_QPT_RC);
	if (IS_ERR(cm_id))
		return PTR_ERR(cm_id);

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = addr;

	
	ret = rdma_bind_addr(cm_id, (struct sockaddr *)&sin);
	
	if (ret || cm_id->device->node_type != RDMA_NODE_RNIC)
		ret = -EADDRNOTAVAIL;

	rdsdebug("STR",
		&addr, ret,
		cm_id->device ? cm_id->device->node_type : -1);

	rdma_destroy_id(cm_id);

	return ret;
}