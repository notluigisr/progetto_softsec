static ssize_t removable_show(struct device *dev, struct device_attribute *attr,
			      char *buf)
{
	return sprintf(buf, "STR", (int)IS_ENABLED(CONFIG_MEMORY_HOTREMOVE));
}