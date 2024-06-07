void pwc_isoc_cleanup(struct pwc_device *pdev)
{
	int i;

	PWC_DEBUG_OPEN("STR");
	if (pdev == NULL)
		return;
	if (pdev->iso_init == 0)
		return;

	
	for (i = 0; i < MAX_ISO_BUFS; i++) {
		struct urb *urb;

		urb = pdev->sbuf[i].urb;
		if (urb != 0) {
			if (pdev->iso_init) {
				PWC_DEBUG_MEMORY("STR", urb);
				usb_kill_urb(urb);
			}
			PWC_DEBUG_MEMORY("STR");
			usb_free_urb(urb);
			pdev->sbuf[i].urb = NULL;
		}
	}

	
	if (pdev->error_status && pdev->error_status != EPIPE) {
		PWC_DEBUG_OPEN("STR");
		usb_set_interface(pdev->udev, 0, 0);
	}

	pdev->iso_init = 0;
	PWC_DEBUG_OPEN("STR");
}