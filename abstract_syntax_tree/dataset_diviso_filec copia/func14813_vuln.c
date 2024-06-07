static void chase_port(struct edgeport_port *port, unsigned long timeout,
								int flush)
{
	int baud_rate;
	struct tty_struct *tty = tty_port_tty_get(&port->port->port);
	struct usb_serial *serial = port->port->serial;
	wait_queue_t wait;
	unsigned long flags;

	if (!timeout)
		timeout = (HZ * EDGE_CLOSING_WAIT)/100;

	
	spin_lock_irqsave(&port->ep_lock, flags);
	init_waitqueue_entry(&wait, current);
	add_wait_queue(&tty->write_wait, &wait);
	for (;;) {
		set_current_state(TASK_INTERRUPTIBLE);
		if (kfifo_len(&port->write_fifo) == 0
		|| timeout == 0 || signal_pending(current)
		|| serial->disconnected)
			
			break;
		spin_unlock_irqrestore(&port->ep_lock, flags);
		timeout = schedule_timeout(timeout);
		spin_lock_irqsave(&port->ep_lock, flags);
	}
	set_current_state(TASK_RUNNING);
	remove_wait_queue(&tty->write_wait, &wait);
	if (flush)
		kfifo_reset_out(&port->write_fifo);
	spin_unlock_irqrestore(&port->ep_lock, flags);
	tty_kref_put(tty);

	
	timeout += jiffies;
	while ((long)(jiffies - timeout) < 0 && !signal_pending(current)
						&& !serial->disconnected) {
		
		if (!tx_active(port))
			break;
		msleep(10);
	}

	
	if (serial->disconnected)
		return;

	
	
	baud_rate = port->baud_rate;
	if (baud_rate == 0)
		baud_rate = 50;
	msleep(max(1, DIV_ROUND_UP(10000, baud_rate)));
}