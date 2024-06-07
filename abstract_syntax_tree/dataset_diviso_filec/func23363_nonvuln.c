evdev_extract_abs_axes(struct evdev_device *device,
		       enum evdev_device_udev_tags udev_tags)
{
	struct libevdev *evdev = device->evdev;
	int fuzz;

	if (!libevdev_has_event_code(evdev, EV_ABS, ABS_X) ||
	    !libevdev_has_event_code(evdev, EV_ABS, ABS_Y))
		 return;

	if (evdev_fix_abs_resolution(device, ABS_X, ABS_Y))
		device->abs.is_fake_resolution = true;

	if (udev_tags & (EVDEV_UDEV_TAG_TOUCHPAD|EVDEV_UDEV_TAG_TOUCHSCREEN)) {
		fuzz = evdev_read_fuzz_prop(device, ABS_X);
		libevdev_set_abs_fuzz(evdev, ABS_X, fuzz);
		fuzz = evdev_read_fuzz_prop(device, ABS_Y);
		libevdev_set_abs_fuzz(evdev, ABS_Y, fuzz);
	}

	device->abs.absinfo_x = libevdev_get_abs_info(evdev, ABS_X);
	device->abs.absinfo_y = libevdev_get_abs_info(evdev, ABS_Y);
	device->abs.dimensions.x = abs(device->abs.absinfo_x->maximum -
				       device->abs.absinfo_x->minimum);
	device->abs.dimensions.y = abs(device->abs.absinfo_y->maximum -
				       device->abs.absinfo_y->minimum);

	if (evdev_is_fake_mt_device(device) ||
	    !libevdev_has_event_code(evdev, EV_ABS, ABS_MT_POSITION_X) ||
	    !libevdev_has_event_code(evdev, EV_ABS, ABS_MT_POSITION_Y))
		 return;

	if (evdev_fix_abs_resolution(device,
				     ABS_MT_POSITION_X,
				     ABS_MT_POSITION_Y))
		device->abs.is_fake_resolution = true;

	if ((fuzz = evdev_read_fuzz_prop(device, ABS_MT_POSITION_X)))
	    libevdev_set_abs_fuzz(evdev, ABS_MT_POSITION_X, fuzz);
	if ((fuzz = evdev_read_fuzz_prop(device, ABS_MT_POSITION_Y)))
	    libevdev_set_abs_fuzz(evdev, ABS_MT_POSITION_Y, fuzz);

	device->abs.absinfo_x = libevdev_get_abs_info(evdev, ABS_MT_POSITION_X);
	device->abs.absinfo_y = libevdev_get_abs_info(evdev, ABS_MT_POSITION_Y);
	device->abs.dimensions.x = abs(device->abs.absinfo_x->maximum -
				       device->abs.absinfo_x->minimum);
	device->abs.dimensions.y = abs(device->abs.absinfo_y->maximum -
				       device->abs.absinfo_y->minimum);
	device->is_mt = 1;
}