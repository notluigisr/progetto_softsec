evdev_accel_config_set_profile(struct libinput_device *libinput_device,
			       enum libinput_config_accel_profile profile)
{
	struct evdev_device *device = evdev_device(libinput_device);
	struct motion_filter *filter;
	double speed;

	filter = device->pointer.filter;
	if (filter_get_type(filter) == profile)
		return LIBINPUT_CONFIG_STATUS_SUCCESS;

	speed = filter_get_speed(filter);
	device->pointer.filter = NULL;

	if (evdev_init_accel(device, profile)) {
		evdev_accel_config_set_speed(libinput_device, speed);
		filter_destroy(filter);
	} else {
		device->pointer.filter = filter;
		return LIBINPUT_CONFIG_STATUS_UNSUPPORTED;
	}

	return LIBINPUT_CONFIG_STATUS_SUCCESS;
}