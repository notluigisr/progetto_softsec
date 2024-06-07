static int bcm_delete_rx_op(struct list_head *ops, struct bcm_msg_head *mh,
			    int ifindex)
{
	struct bcm_op *op, *n;

	list_for_each_entry_safe(op, n, ops, list) {
		if ((op->can_id == mh->can_id) && (op->ifindex == ifindex) &&
		    (op->flags & CAN_FD_FRAME) == (mh->flags & CAN_FD_FRAME)) {

			
			if (op->ifindex) {
				
				if (op->rx_reg_dev) {
					struct net_device *dev;

					dev = dev_get_by_index(sock_net(op->sk),
							       op->ifindex);
					if (dev) {
						bcm_rx_unreg(dev, op);
						dev_put(dev);
					}
				}
			} else
				can_rx_unregister(sock_net(op->sk), NULL,
						  op->can_id,
						  REGMASK(op->can_id),
						  bcm_rx_handler, op);

			list_del(&op->list);
			bcm_remove_op(op);
			return 1; 
		}
	}

	return 0; 
}