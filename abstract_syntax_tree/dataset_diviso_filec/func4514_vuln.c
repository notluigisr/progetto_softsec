static int n_hdlc_tty_ioctl(struct tty_struct *tty, struct file *file,
			    unsigned int cmd, unsigned long arg)
{
	struct n_hdlc *n_hdlc = tty2n_hdlc (tty);
	int error = 0;
	int count;
	unsigned long flags;
	
	if (debuglevel >= DEBUG_LEVEL_INFO)	
		printk("STR",
			__FILE__,__LINE__,cmd);
		
	
	if (!n_hdlc || n_hdlc->magic != HDLC_MAGIC)
		return -EBADF;

	switch (cmd) {
	case FIONREAD:
		
		
		spin_lock_irqsave(&n_hdlc->rx_buf_list.spinlock,flags);
		if (n_hdlc->rx_buf_list.head)
			count = n_hdlc->rx_buf_list.head->count;
		else
			count = 0;
		spin_unlock_irqrestore(&n_hdlc->rx_buf_list.spinlock,flags);
		error = put_user(count, (int __user *)arg);
		break;

	case TIOCOUTQ:
		
		count = tty_chars_in_buffer(tty);
		
		spin_lock_irqsave(&n_hdlc->tx_buf_list.spinlock,flags);
		if (n_hdlc->tx_buf_list.head)
			count += n_hdlc->tx_buf_list.head->count;
		spin_unlock_irqrestore(&n_hdlc->tx_buf_list.spinlock,flags);
		error = put_user(count, (int __user *)arg);
		break;

	case TCFLSH:
		switch (arg) {
		case TCIOFLUSH:
		case TCOFLUSH:
			flush_tx_queue(tty);
		}
		

	default:
		error = n_tty_ioctl_helper(tty, file, cmd, arg);
		break;
	}
	return error;
	
}	