static void peak_usb_read_bulk_callback(struct urb *urb)
{
	struct peak_usb_device *dev = urb->context;
	struct net_device *netdev;
	int err;

	netdev = dev->netdev;

	if (!netif_device_present(netdev))
		return;

	
	switch (urb->status) {
	case 0:
		
		break;

	case -EILSEQ:
	case -ENOENT:
	case -ECONNRESET:
	case -ESHUTDOWN:
		return;

	default:
		if (net_ratelimit())
			netdev_err(netdev,
				   "STR", urb->status);
		goto resubmit_urb;
	}

	
	if ((urb->actual_length > 0) && (dev->adapter->dev_decode_buf)) {
		
		if (dev->state & PCAN_USB_STATE_STARTED) {
			err = dev->adapter->dev_decode_buf(dev, urb);
			if (err)
				pcan_dump_mem("STR",
					      urb->transfer_buffer,
					      urb->transfer_buffer_length);
		}
	}

resubmit_urb:
	usb_fill_bulk_urb(urb, dev->udev,
		usb_rcvbulkpipe(dev->udev, dev->ep_msg_in),
		urb->transfer_buffer, dev->adapter->rx_buffer_size,
		peak_usb_read_bulk_callback, dev);

	usb_anchor_urb(urb, &dev->rx_submitted);
	err = usb_submit_urb(urb, GFP_ATOMIC);
	if (!err)
		return;

	usb_unanchor_urb(urb);

	if (err == -ENODEV)
		netif_device_detach(netdev);
	else
		netdev_err(netdev, "STR",
			   err);
}