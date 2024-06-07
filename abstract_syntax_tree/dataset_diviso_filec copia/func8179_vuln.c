static void p54u_disconnect(struct usb_interface *intf)
{
	struct ieee80211_hw *dev = usb_get_intfdata(intf);
	struct p54u_priv *priv;

	if (!dev)
		return;

	priv = dev->priv;
	wait_for_completion(&priv->fw_wait_load);
	p54_unregister_common(dev);

	usb_put_dev(interface_to_usbdev(intf));
	release_firmware(priv->fw);
	p54_free_common(dev);
}