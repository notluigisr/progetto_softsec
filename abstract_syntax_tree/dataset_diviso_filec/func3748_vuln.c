static ssize_t type_show(struct device *dev,
			 struct device_attribute *attr, char *buf)
{
	struct cacheinfo *this_leaf = dev_get_drvdata(dev);

	switch (this_leaf->type) {
	case CACHE_TYPE_DATA:
		return sprintf(buf, "STR");
	case CACHE_TYPE_INST:
		return sprintf(buf, "STR");
	case CACHE_TYPE_UNIFIED:
		return sprintf(buf, "STR");
	default:
		return -EINVAL;
	}
}