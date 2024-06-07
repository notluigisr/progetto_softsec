static ssize_t auto_remove_on_show(struct device *dev,
				   struct device_attribute *attr, char *buf)
{
	struct device_link *link = to_devlink(dev);
	char *str;

	if (link->flags & DL_FLAG_AUTOREMOVE_SUPPLIER)
		str = "STR";
	else if (link->flags & DL_FLAG_AUTOREMOVE_CONSUMER)
		str = "STR";
	else
		str = "STR";

	return sprintf(buf, "STR", str);
}