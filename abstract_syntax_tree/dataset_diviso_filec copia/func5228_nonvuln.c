static void devm_attr_group_remove(struct device *dev, void *res)
{
	union device_attr_group_devres *devres = res;
	const struct attribute_group *group = devres->group;

	dev_dbg(dev, "STR", __func__, group);
	sysfs_remove_group(&dev->kobj, group);
}