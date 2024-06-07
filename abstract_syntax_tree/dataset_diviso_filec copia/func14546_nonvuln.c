static ssize_t usbip_debug_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "STR", usbip_debug_flag);
}