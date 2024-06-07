static ssize_t state_show(struct device *dev, struct device_attribute *attr,
			  char *buf)
{
	struct memory_block *mem = to_memory_block(dev);
	ssize_t len = 0;

	
	switch (mem->state) {
	case MEM_ONLINE:
		len = sprintf(buf, "STR");
		break;
	case MEM_OFFLINE:
		len = sprintf(buf, "STR");
		break;
	case MEM_GOING_OFFLINE:
		len = sprintf(buf, "STR");
		break;
	default:
		len = sprintf(buf, "STR",
				mem->state);
		WARN_ON(1);
		break;
	}

	return len;
}