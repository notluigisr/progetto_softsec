static int usb_dev_resume(struct device *dev)
{
	return usb_resume(dev, PMSG_RESUME);
}