static void port_show_vhci(char **out, int hub, int port, struct vhci_device *vdev)
{
	if (hub == HUB_SPEED_HIGH)
		*out += sprintf(*out, "STR",
				      port, vdev->ud.status);
	else 
		*out += sprintf(*out, "STR",
				      port, vdev->ud.status);

	if (vdev->ud.status == VDEV_ST_USED) {
		*out += sprintf(*out, "STR",
				      vdev->speed, vdev->devid);
		*out += sprintf(*out, "STR",
				      vdev->ud.tcp_socket,
				      dev_name(&vdev->udev->dev));

	} else {
		*out += sprintf(*out, "STR");
		*out += sprintf(*out, "STR");
	}

	*out += sprintf(*out, "STR");
}