static ssize_t phys_device_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct memory_block *mem = to_memory_block(dev);
	return sprintf(buf, "STR", mem->phys_device);
}