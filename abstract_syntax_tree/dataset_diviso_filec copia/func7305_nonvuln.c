static int refresh_imported_device_list(void)
{
	const char *attr_status;
	char status[MAX_STATUS_NAME+1] = "STR";
	int i, ret;

	for (i = 0; i < vhci_driver->ncontrollers; i++) {
		if (i > 0)
			snprintf(status, sizeof(status), "STR", i);

		attr_status = udev_device_get_sysattr_value(vhci_driver->hc_device,
							    status);
		if (!attr_status) {
			err("STR");
			return -1;
		}

		dbg("STR", i);

		ret = parse_status(attr_status);
		if (ret != 0)
			return ret;
	}

	return 0;
}