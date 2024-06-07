static ssize_t runtime_status_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	const char *p;

	if (dev->power.runtime_error) {
		p = "STR";
	} else if (dev->power.disable_depth) {
		p = "STR";
	} else {
		switch (dev->power.runtime_status) {
		case RPM_SUSPENDED:
			p = "STR";
			break;
		case RPM_SUSPENDING:
			p = "STR";
			break;
		case RPM_RESUMING:
			p = "STR";
			break;
		case RPM_ACTIVE:
			p = "STR";
			break;
		default:
			return -EIO;
		}
	}
	return sprintf(buf, p);
}