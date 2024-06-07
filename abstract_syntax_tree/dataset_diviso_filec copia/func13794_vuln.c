static ssize_t status_show(struct device *dev,
			  struct device_attribute *attr, char *buf)
{
	char *status;

	switch (to_devlink(dev)->status) {
	case DL_STATE_NONE:
		status = "STR"; break;
	case DL_STATE_DORMANT:
		status = "STR"; break;
	case DL_STATE_AVAILABLE:
		status = "STR"; break;
	case DL_STATE_CONSUMER_PROBE:
		status = "STR"; break;
	case DL_STATE_ACTIVE:
		status = "STR"; break;
	case DL_STATE_SUPPLIER_UNBIND:
		status = "STR"; break;
	default:
		status = "STR"; break;
	}
	return sprintf(buf, "STR", status);
}