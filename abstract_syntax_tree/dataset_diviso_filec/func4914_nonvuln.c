evdev_transform_absolute(struct evdev_device *device,
			 struct device_coords *point)
{
	if (!device->abs.apply_calibration)
		return;

	matrix_mult_vec(&device->abs.calibration, &point->x, &point->y);
}