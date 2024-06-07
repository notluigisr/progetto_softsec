static int bnx2x_prev_mark_path(struct bnx2x *bp, bool after_undi)
{
	struct bnx2x_prev_path_list *tmp_list;
	int rc;

	rc = down_interruptible(&bnx2x_prev_sem);
	if (rc) {
		BNX2X_ERR("STR", rc);
		return rc;
	}

	
	tmp_list = bnx2x_prev_path_get_entry(bp);
	if (tmp_list) {
		if (!tmp_list->aer) {
			BNX2X_ERR("STR");
		} else {
			DP(NETIF_MSG_HW, "STR",
			   BP_PATH(bp));
			tmp_list->aer = 0;
		}
		up(&bnx2x_prev_sem);
		return 0;
	}
	up(&bnx2x_prev_sem);

	
	tmp_list = kmalloc(sizeof(struct bnx2x_prev_path_list), GFP_KERNEL);
	if (!tmp_list) {
		BNX2X_ERR("STR");
		return -ENOMEM;
	}

	tmp_list->bus = bp->pdev->bus->number;
	tmp_list->slot = PCI_SLOT(bp->pdev->devfn);
	tmp_list->path = BP_PATH(bp);
	tmp_list->aer = 0;
	tmp_list->undi = after_undi ? (1 << BP_PORT(bp)) : 0;

	rc = down_interruptible(&bnx2x_prev_sem);
	if (rc) {
		BNX2X_ERR("STR", rc);
		kfree(tmp_list);
	} else {
		DP(NETIF_MSG_HW, "STR",
		   BP_PATH(bp));
		list_add(&tmp_list->list, &bnx2x_prev_list);
		up(&bnx2x_prev_sem);
	}

	return rc;
}