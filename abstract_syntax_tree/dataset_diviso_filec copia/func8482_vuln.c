static ssize_t runtime_enabled_show(struct device *dev,
				    struct device_attribute *attr, char *buf)
{
	if (dev->power.disable_depth && (dev->power.runtime_auto == false))
		return sprintf(buf, "STR");
	if (dev->power.disable_depth)
		return sprintf(buf, "STR");
	if (dev->power.runtime_auto == false)
		return sprintf(buf, "STR");
	return sprintf(buf, "STR");
}