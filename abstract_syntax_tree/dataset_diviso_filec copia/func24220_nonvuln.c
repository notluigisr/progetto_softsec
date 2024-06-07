evdev_device_get_id_product(struct evdev_device *device)
{
	return libevdev_get_id_product(device->evdev);
}