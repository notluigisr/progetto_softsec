static ssize_t block_size_bytes_show(struct device *dev,
				     struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "STR", memory_block_size_bytes());
}