evdev_log_msg(struct evdev_device *device,
	      enum libinput_log_priority priority,
	      const char *format,
	      ...)
{
	va_list args;
	char buf[1024];

	if (!is_logged(evdev_libinput_context(device), priority))
		return;

	
	snprintf(buf,
		 sizeof(buf),
		 "STR",
		 evdev_device_get_sysname(device),
		 (priority > LIBINPUT_LOG_PRIORITY_DEBUG) ?  device->devname : "",
		 (priority > LIBINPUT_LOG_PRIORITY_DEBUG) ?  "STR",
		 format);

	va_start(args, format);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "STR"
	log_msg_va(evdev_libinput_context(device), priority, buf, args);
#pragma GCC diagnostic pop
	va_end(args);

}