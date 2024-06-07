static void edge_bulk_in_callback(struct urb *urb)
{
	struct edgeport_port *edge_port = urb->context;
	struct device *dev = &edge_port->port->dev;
	unsigned char *data = urb->transfer_buffer;
	int retval = 0;
	int port_number;
	int status = urb->status;

	switch (status) {
	case 0:
		
		break;
	case -ECONNRESET:
	case -ENOENT:
	case -ESHUTDOWN:
		
		dev_dbg(&urb->dev->dev, "STR", __func__, status);
		return;
	default:
		dev_err(&urb->dev->dev, "STR", __func__, status);
	}

	if (status == -EPIPE)
		goto exit;

	if (status) {
		dev_err(&urb->dev->dev, "STR", __func__);
		return;
	}

	port_number = edge_port->port->port_number;

	if (edge_port->lsr_event) {
		edge_port->lsr_event = 0;
		dev_dbg(dev, "STR",
			__func__, port_number, edge_port->lsr_mask, *data);
		handle_new_lsr(edge_port, 1, edge_port->lsr_mask, *data);
		
		--urb->actual_length;
		++data;
	}

	if (urb->actual_length) {
		usb_serial_debug_data(dev, __func__, urb->actual_length, data);
		if (edge_port->close_pending)
			dev_dbg(dev, "STR",
								__func__);
		else
			edge_tty_recv(edge_port->port, data,
					urb->actual_length);
		edge_port->port->icount.rx += urb->actual_length;
	}

exit:
	
	spin_lock(&edge_port->ep_lock);
	if (edge_port->ep_read_urb_state == EDGE_READ_URB_RUNNING)
		retval = usb_submit_urb(urb, GFP_ATOMIC);
	else if (edge_port->ep_read_urb_state == EDGE_READ_URB_STOPPING)
		edge_port->ep_read_urb_state = EDGE_READ_URB_STOPPED;

	spin_unlock(&edge_port->ep_lock);
	if (retval)
		dev_err(dev, "STR", __func__, retval);
}