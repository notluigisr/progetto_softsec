struct soc_device *soc_device_register(struct soc_device_attribute *soc_dev_attr)
{
	struct soc_device *soc_dev;
	const struct attribute_group **soc_attr_groups;
	int ret;

	if (!soc_bus_type.p) {
		if (early_soc_dev_attr)
			return ERR_PTR(-EBUSY);
		early_soc_dev_attr = soc_dev_attr;
		return NULL;
	}

	soc_dev = kzalloc(sizeof(*soc_dev), GFP_KERNEL);
	if (!soc_dev) {
		ret = -ENOMEM;
		goto out1;
	}

	soc_attr_groups = kcalloc(3, sizeof(*soc_attr_groups), GFP_KERNEL);
	if (!soc_attr_groups) {
		ret = -ENOMEM;
		goto out2;
	}
	soc_attr_groups[0] = &soc_attr_group;
	soc_attr_groups[1] = soc_dev_attr->custom_attr_group;

	
	ret = ida_simple_get(&soc_ida, 0, 0, GFP_KERNEL);
	if (ret < 0)
		goto out3;
	soc_dev->soc_dev_num = ret;

	soc_dev->attr = soc_dev_attr;
	soc_dev->dev.bus = &soc_bus_type;
	soc_dev->dev.groups = soc_attr_groups;
	soc_dev->dev.release = soc_release;

	dev_set_name(&soc_dev->dev, "STR", soc_dev->soc_dev_num);

	ret = device_register(&soc_dev->dev);
	if (ret) {
		put_device(&soc_dev->dev);
		return ERR_PTR(ret);
	}

	return soc_dev;

out3:
	kfree(soc_attr_groups);
out2:
	kfree(soc_dev);
out1:
	return ERR_PTR(ret);
}