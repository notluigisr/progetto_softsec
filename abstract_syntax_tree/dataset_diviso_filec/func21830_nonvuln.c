static inline int temac_check_tx_bd_space(struct temac_local *lp, int num_frag)
{
	struct cdmac_bd *cur_p;
	int tail;

	tail = lp->tx_bd_tail;
	cur_p = &lp->tx_bd_v[tail];

	do {
		if (cur_p->app0)
			return NETDEV_TX_BUSY;

		
		rmb();

		tail++;
		if (tail >= lp->tx_bd_num)
			tail = 0;

		cur_p = &lp->tx_bd_v[tail];
		num_frag--;
	} while (num_frag >= 0);

	return 0;
}