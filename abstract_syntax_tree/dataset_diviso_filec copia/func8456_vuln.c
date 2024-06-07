static unsigned int n_hdlc_tty_poll(struct tty_struct *tty, struct file *filp,
				    poll_table *wait)
{
	struct n_hdlc *n_hdlc = tty2n_hdlc (tty);
	unsigned int mask = 0;

	if (debuglevel >= DEBUG_LEVEL_INFO)	
		printk("STR",__FILE__,__LINE__);
		
	if (n_hdlc && n_hdlc->magic == HDLC_MAGIC && tty == n_hdlc->tty) {
		
		

		poll_wait(filp, &tty->read_wait, wait);
		poll_wait(filp, &tty->write_wait, wait);

		
		if (n_hdlc->rx_buf_list.head)
			mask |= POLLIN | POLLRDNORM;	
		if (test_bit(TTY_OTHER_CLOSED, &tty->flags))
			mask |= POLLHUP;
		if (tty_hung_up_p(filp))
			mask |= POLLHUP;
		if (!tty_is_writelocked(tty) &&
				n_hdlc->tx_free_buf_list.head)
			mask |= POLLOUT | POLLWRNORM;	
	}
	return mask;
}	