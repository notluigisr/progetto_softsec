static ssize_t driver_override_store(struct device *_dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count)
{
	struct amba_device *dev = to_amba_device(_dev);
	char *driver_override, *old = dev->driver_override, *cp;

	
	if (count >= (PAGE_SIZE - 1))
		return -EINVAL;

	driver_override = kstrndup(buf, count, GFP_KERNEL);
	if (!driver_override)
		return -ENOMEM;

	cp = strchr(driver_override, '\n');
	if (cp)
		*cp = '\0';

	if (strlen(driver_override)) {
		dev->driver_override = driver_override;
	} else {
	       kfree(driver_override);
	       dev->driver_override = NULL;
	}

	kfree(old);

	return count;
}