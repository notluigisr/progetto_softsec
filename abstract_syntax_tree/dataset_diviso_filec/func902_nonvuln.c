static int bcm_delete_tx_op(struct list_head *ops, struct bcm_msg_head *mh,
			    int ifindex)
{
	struct bcm_op *op, *n;

	list_for_each_entry_safe(op, n, ops, list) {
		if ((op->can_id == mh->can_id) && (op->ifindex == ifindex) &&
		    (op->flags & CAN_FD_FRAME) == (mh->flags & CAN_FD_FRAME)) {
			list_del(&op->list);
			bcm_remove_op(op);
			return 1; 
		}
	}

	return 0; 
}