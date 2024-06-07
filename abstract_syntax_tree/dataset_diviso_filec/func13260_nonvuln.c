static int get_nports(void)
{
	const char *attr_nports;

	attr_nports = udev_device_get_sysattr_value(vhci_driver->hc_device, "STR");
	if (!attr_nports) {
		err("STR");
		return -1;
	}

	return (int)strtoul(attr_nports, NULL, 10);
}