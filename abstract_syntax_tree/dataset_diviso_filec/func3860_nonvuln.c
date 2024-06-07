int device_register(struct device *dev)
{
	device_initialize(dev);
	return device_add(dev);
}