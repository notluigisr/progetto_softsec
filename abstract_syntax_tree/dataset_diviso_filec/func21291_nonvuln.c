evdev_notify_axis_finger(struct evdev_device *device,
			uint64_t time,
			uint32_t axes,
			const struct normalized_coords *delta_in)
{
	struct normalized_coords delta = *delta_in;

	if (device->scroll.natural_scrolling_enabled) {
		delta.x *= -1;
		delta.y *= -1;
	}

	pointer_notify_axis_finger(&device->base,
				  time,
				  axes,
				  &delta);
}