static void usb_pwc_disconnect(struct usb_interface *intf)
{
	struct pwc_device *pdev;
	int hint;

	lock_kernel();
	pdev = usb_get_intfdata (intf);
	usb_set_intfdata (intf, NULL);
	if (pdev == NULL) {
		PWC_ERROR("STR");
		goto disconnect_out;
	}
	if (pdev->udev == NULL) {
		PWC_ERROR("STR", pdev);
		goto disconnect_out;
	}
	if (pdev->udev != interface_to_usbdev(intf)) {
		PWC_ERROR("STR");
		goto disconnect_out;
	}

	
	if (pdev->vopen) {
		PWC_INFO("STR");
		pdev->error_status = EPIPE;
	}

	
	wake_up_interruptible(&pdev->frameq);
	
	while (pdev->vopen)
		schedule();
	
	PWC_DEBUG_PROBE("STR");
	pwc_remove_sysfs_files(pdev->vdev);
	video_unregister_device(pdev->vdev);

	
	kfree(pdev);

disconnect_out:
	
	for (hint = 0; hint < MAX_DEV_HINTS; hint++)
		if (device_hint[hint].pdev == pdev)
			device_hint[hint].pdev = NULL;

	unlock_kernel();
}