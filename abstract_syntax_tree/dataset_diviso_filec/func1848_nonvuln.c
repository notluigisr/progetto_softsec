static void visor_read_int_callback(struct urb *urb)
{
	struct usb_serial_port *port = urb->context;
	int status = urb->status;
	int result;

	switch (status) {
	case 0:
		
		break;
	case -ECONNRESET:
	case -ENOENT:
	case -ESHUTDOWN:
		
		dev_dbg(&port->dev, "STR",
			__func__, status);
		return;
	default:
		dev_dbg(&port->dev, "STR",
			__func__, status);
		goto exit;
	}

	
	usb_serial_debug_data(&port->dev, __func__, urb->actual_length,
			      urb->transfer_buffer);

exit:
	result = usb_submit_urb(urb, GFP_ATOMIC);
	if (result)
		dev_err(&urb->dev->dev,
				"STR",
							__func__, result);
}