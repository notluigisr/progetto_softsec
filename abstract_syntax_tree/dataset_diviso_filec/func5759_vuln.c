static ssize_t control_show(struct device *dev, struct device_attribute *attr,
			    char *buf)
{
	return sprintf(buf, "STR",
				dev->power.runtime_auto ? ctrl_auto : ctrl_on);
}