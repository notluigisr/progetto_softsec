static ssize_t size_show(struct device *dev,
			 struct device_attribute *attr, char *buf)
{
	struct cacheinfo *this_leaf = dev_get_drvdata(dev);

	return sprintf(buf, "STR", this_leaf->size >> 10);
}