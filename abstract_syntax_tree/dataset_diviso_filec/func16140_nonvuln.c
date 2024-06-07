int bnx2x_alloc_mem_cnic(struct bnx2x *bp)
{
	if (!CHIP_IS_E1x(bp)) {
		
		bp->cnic_sb.e2_sb = BNX2X_PCI_ALLOC(&bp->cnic_sb_mapping,
						    sizeof(struct host_hc_status_block_e2));
		if (!bp->cnic_sb.e2_sb)
			goto alloc_mem_err;
	} else {
		bp->cnic_sb.e1x_sb = BNX2X_PCI_ALLOC(&bp->cnic_sb_mapping,
						     sizeof(struct host_hc_status_block_e1x));
		if (!bp->cnic_sb.e1x_sb)
			goto alloc_mem_err;
	}

	if (CONFIGURE_NIC_MODE(bp) && !bp->t2) {
		
		bp->t2 = BNX2X_PCI_ALLOC(&bp->t2_mapping, SRC_T2_SZ);
		if (!bp->t2)
			goto alloc_mem_err;
	}

	
	bp->cnic_eth_dev.addr_drv_info_to_mcp =
		&bp->slowpath->drv_info_to_mcp;

	if (bnx2x_ilt_mem_op_cnic(bp, ILT_MEMOP_ALLOC))
		goto alloc_mem_err;

	return 0;

alloc_mem_err:
	bnx2x_free_mem_cnic(bp);
	BNX2X_ERR("STR");
	return -ENOMEM;
}