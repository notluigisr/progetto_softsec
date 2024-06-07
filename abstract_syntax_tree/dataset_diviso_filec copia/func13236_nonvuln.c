static ssize_t show_tabletModelCode(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct aiptek *aiptek = dev_get_drvdata(dev);

	return snprintf(buf, PAGE_SIZE, "STR", aiptek->features.modelCode);
}