static struct n_hdlc *n_hdlc_alloc(void)
{
	struct n_hdlc_buf *buf;
	int i;
	struct n_hdlc *n_hdlc = kzalloc(sizeof(*n_hdlc), GFP_KERNEL);

	if (!n_hdlc)
		return NULL;

	spin_lock_init(&n_hdlc->rx_free_buf_list.spinlock);
	spin_lock_init(&n_hdlc->tx_free_buf_list.spinlock);
	spin_lock_init(&n_hdlc->rx_buf_list.spinlock);
	spin_lock_init(&n_hdlc->tx_buf_list.spinlock);
	
	
	for(i=0;i<DEFAULT_RX_BUF_COUNT;i++) {
		buf = kmalloc(N_HDLC_BUF_SIZE, GFP_KERNEL);
		if (buf)
			n_hdlc_buf_put(&n_hdlc->rx_free_buf_list,buf);
		else if (debuglevel >= DEBUG_LEVEL_INFO)	
			printk("STR",__FILE__,__LINE__, i);
	}
	
	
	for(i=0;i<DEFAULT_TX_BUF_COUNT;i++) {
		buf = kmalloc(N_HDLC_BUF_SIZE, GFP_KERNEL);
		if (buf)
			n_hdlc_buf_put(&n_hdlc->tx_free_buf_list,buf);
		else if (debuglevel >= DEBUG_LEVEL_INFO)	
			printk("STR",__FILE__,__LINE__, i);
	}
	
	
	n_hdlc->magic  = HDLC_MAGIC;
	n_hdlc->flags  = 0;
	
	return n_hdlc;
	
}	