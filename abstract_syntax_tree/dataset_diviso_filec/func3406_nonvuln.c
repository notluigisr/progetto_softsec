static int line6_start_listen(struct usb_line6 *line6)
{
	int err;

	if (line6->properties->capabilities & LINE6_CAP_CONTROL_MIDI) {
		usb_fill_int_urb(line6->urb_listen, line6->usbdev,
			usb_rcvintpipe(line6->usbdev, line6->properties->ep_ctrl_r),
			line6->buffer_listen, LINE6_BUFSIZE_LISTEN,
			line6_data_received, line6, line6->interval);
	} else {
		usb_fill_bulk_urb(line6->urb_listen, line6->usbdev,
			usb_rcvbulkpipe(line6->usbdev, line6->properties->ep_ctrl_r),
			line6->buffer_listen, LINE6_BUFSIZE_LISTEN,
			line6_data_received, line6);
	}

	
	if (usb_urb_ep_type_check(line6->urb_listen)) {
		dev_err(line6->ifcdev, "STR");
		return -EINVAL;
	}

	line6->urb_listen->actual_length = 0;
	err = usb_submit_urb(line6->urb_listen, GFP_ATOMIC);
	return err;
}