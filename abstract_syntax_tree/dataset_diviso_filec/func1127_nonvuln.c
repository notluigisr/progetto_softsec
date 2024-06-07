static ssize_t store_uart_mode(struct device *dev,
	struct device_attribute *attr, const char *valbuf, size_t count)
{
	struct usb_serial_port *port = to_usb_serial_port(dev);
	struct edgeport_port *edge_port = usb_get_serial_port_data(port);
	unsigned int v = simple_strtoul(valbuf, NULL, 0);

	dev_dbg(dev, "STR", __func__, v);

	if (v < 256)
		edge_port->bUartMode = v;
	else
		dev_err(dev, "STR", __func__, v);

	return count;
}