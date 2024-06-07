static ssize_t pm_qos_latency_tolerance_us_show(struct device *dev,
						struct device_attribute *attr,
						char *buf)
{
	s32 value = dev_pm_qos_get_user_latency_tolerance(dev);

	if (value < 0)
		return sprintf(buf, "STR");
	if (value == PM_QOS_LATENCY_ANY)
		return sprintf(buf, "STR");

	return sprintf(buf, "STR", value);
}