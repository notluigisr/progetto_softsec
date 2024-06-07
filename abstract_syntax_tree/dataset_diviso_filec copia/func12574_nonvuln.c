evdev_reject_device(struct evdev_device *device)
{
	struct libevdev *evdev = device->evdev;
	unsigned int code;
	const struct input_absinfo *absx, *absy;

	if (libevdev_has_event_code(evdev, EV_ABS, ABS_X) ^
	    libevdev_has_event_code(evdev, EV_ABS, ABS_Y))
		return true;

	if (libevdev_has_event_code(evdev, EV_REL, REL_X) ^
	    libevdev_has_event_code(evdev, EV_REL, REL_Y))
		return true;

	if (!evdev_is_fake_mt_device(device) &&
	    libevdev_has_event_code(evdev, EV_ABS, ABS_MT_POSITION_X) ^
	    libevdev_has_event_code(evdev, EV_ABS, ABS_MT_POSITION_Y))
		return true;

	if (libevdev_has_event_code(evdev, EV_ABS, ABS_X)) {
		absx = libevdev_get_abs_info(evdev, ABS_X);
		absy = libevdev_get_abs_info(evdev, ABS_Y);
		if ((absx->resolution == 0 && absy->resolution != 0) ||
		    (absx->resolution != 0 && absy->resolution == 0)) {
			evdev_log_bug_kernel(device,
				       "STR");
			return true;
		}
	}

	if (!evdev_is_fake_mt_device(device) &&
	    libevdev_has_event_code(evdev, EV_ABS, ABS_MT_POSITION_X)) {
		absx = libevdev_get_abs_info(evdev, ABS_MT_POSITION_X);
		absy = libevdev_get_abs_info(evdev, ABS_MT_POSITION_Y);
		if ((absx->resolution == 0 && absy->resolution != 0) ||
		    (absx->resolution != 0 && absy->resolution == 0)) {
			evdev_log_bug_kernel(device,
				       "STR");
			return true;
		}
	}

	for (code = 0; code < ABS_CNT; code++) {
		switch (code) {
		case ABS_MISC:
		case ABS_MT_SLOT:
		case ABS_MT_TOOL_TYPE:
			break;
		default:
			if (!evdev_check_min_max(device, code))
				return true;
		}
	}

	return false;
}