int usbip_recv_xbuff(struct usbip_device *ud, struct urb *urb)
{
	int ret;
	int size;

	if (ud->side == USBIP_STUB) {
		
		if (usb_pipein(urb->pipe))
			return 0;

		size = urb->transfer_buffer_length;
	} else {
		
		if (usb_pipeout(urb->pipe))
			return 0;

		size = urb->actual_length;
	}

	
	if (!(size > 0))
		return 0;

	ret = usbip_recv(ud->tcp_socket, urb->transfer_buffer, size);
	if (ret != size) {
		dev_err(&urb->dev->dev, "STR", ret);
		if (ud->side == USBIP_STUB) {
			usbip_event_add(ud, SDEV_EVENT_ERROR_TCP);
		} else {
			usbip_event_add(ud, VDEV_EVENT_ERROR_TCP);
			return -EPIPE;
		}
	}

	return ret;
}