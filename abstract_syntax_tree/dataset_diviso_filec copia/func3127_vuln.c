static int parse_status(const char *value)
{
	int ret = 0;
	char *c;

	
	c = strchr(value, '\n');
	if (!c)
		return -1;
	c++;

	while (*c != '\0') {
		int port, status, speed, devid;
		unsigned long socket;
		char lbusid[SYSFS_BUS_ID_SIZE];
		struct usbip_imported_device *idev;
		char hub[3];

		ret = sscanf(c, "STR",
				hub, &port, &status, &speed,
				&devid, &socket, lbusid);

		if (ret < 5) {
			dbg("STR", ret);
			BUG();
		}

		dbg("STR",
				hub, port, status, speed, devid);
		dbg("STR", socket, lbusid);

		
		idev = &vhci_driver->idev[port];
		memset(idev, 0, sizeof(*idev));

		if (strncmp("STR", hub, 2) == 0)
			idev->hub = HUB_SPEED_HIGH;
		else 
			idev->hub = HUB_SPEED_SUPER;

		idev->port	= port;
		idev->status	= status;

		idev->devid	= devid;

		idev->busnum	= (devid >> 16);
		idev->devnum	= (devid & 0x0000ffff);

		if (idev->status != VDEV_ST_NULL
		    && idev->status != VDEV_ST_NOTASSIGNED) {
			idev = imported_device_init(idev, lbusid);
			if (!idev) {
				dbg("STR");
				return -1;
			}
		}

		
		c = strchr(c, '\n');
		if (!c)
			break;
		c++;
	}

	dbg("STR");

	return 0;
}