static void hub_power_on(struct usb_hub *hub, bool do_delay)
{
	int port1;

	
	if (hub_is_port_power_switchable(hub))
		dev_dbg(hub->intfdev, "STR");
	else
		dev_dbg(hub->intfdev, "STR"
				"STR");
	for (port1 = 1; port1 <= hub->hdev->maxchild; port1++)
		if (test_bit(port1, hub->power_bits))
			set_port_feature(hub->hdev, port1, USB_PORT_FEAT_POWER);
		else
			usb_clear_port_feature(hub->hdev, port1,
						USB_PORT_FEAT_POWER);
	if (do_delay)
		msleep(hub_power_on_good_delay(hub));
}