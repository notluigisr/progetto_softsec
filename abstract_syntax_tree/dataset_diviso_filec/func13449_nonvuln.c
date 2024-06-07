static void edge_close(struct usb_serial_port *port)
{
	struct edgeport_serial *edge_serial;
	struct edgeport_port *edge_port;
	struct usb_serial *serial = port->serial;
	unsigned long flags;
	int port_number;

	edge_serial = usb_get_serial_data(port->serial);
	edge_port = usb_get_serial_port_data(port);
	if (edge_serial == NULL || edge_port == NULL)
		return;

	
	edge_port->close_pending = 1;

	usb_kill_urb(port->read_urb);
	usb_kill_urb(port->write_urb);
	edge_port->ep_write_urb_in_use = 0;
	spin_lock_irqsave(&edge_port->ep_lock, flags);
	kfifo_reset_out(&port->write_fifo);
	spin_unlock_irqrestore(&edge_port->ep_lock, flags);

	dev_dbg(&port->dev, "STR", __func__);
	port_number = port->port_number;
	send_cmd(serial->dev, UMPC_CLOSE_PORT,
		     (__u8)(UMPM_UART1_PORT + port_number), 0, NULL, 0);

	mutex_lock(&edge_serial->es_lock);
	--edge_port->edge_serial->num_ports_open;
	if (edge_port->edge_serial->num_ports_open <= 0) {
		
		usb_kill_urb(port->serial->port[0]->interrupt_in_urb);
		edge_port->edge_serial->num_ports_open = 0;
	}
	mutex_unlock(&edge_serial->es_lock);
	edge_port->close_pending = 0;
}