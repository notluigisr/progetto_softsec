static int hub_resume(struct usb_interface *intf)
{
	struct usb_hub *hub = usb_get_intfdata(intf);

	dev_dbg(&intf->dev, "STR", __func__);
	hub_activate(hub, HUB_RESUME);

	
	report_wakeup_requests(hub);
	return 0;
}