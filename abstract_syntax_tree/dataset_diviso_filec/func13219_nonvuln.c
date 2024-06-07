static void peak_usb_unlink_all_urbs(struct peak_usb_device *dev)
{
	int i;

	
	usb_kill_anchored_urbs(&dev->rx_submitted);

	
	for (i = 0; i < PCAN_USB_MAX_TX_URBS; i++) {
		struct urb *urb = dev->tx_contexts[i].urb;

		if (!urb ||
		    dev->tx_contexts[i].echo_index != PCAN_USB_MAX_TX_URBS) {
			
			continue;
		}

		usb_free_urb(urb);
		dev->tx_contexts[i].urb = NULL;
	}

	
	usb_kill_anchored_urbs(&dev->tx_submitted);
	atomic_set(&dev->active_tx_urbs, 0);
}