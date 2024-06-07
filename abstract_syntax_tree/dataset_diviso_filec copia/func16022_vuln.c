static void input_device_enter_reconnect_mode(struct input_device *idev)
{
	DBG("STR", idev->path,
				reconnect_mode_to_string(idev->reconnect_mode));

	
	if (idev->reconnect_mode != RECONNECT_ANY &&
				idev->reconnect_mode != RECONNECT_HOST)
		return;

	
	if (device_is_temporary(idev->device) ||
					btd_device_is_connected(idev->device))
		return;

	if (idev->reconnect_timer > 0)
		g_source_remove(idev->reconnect_timer);

	DBG("STR");
	idev->reconnect_attempt = 0;
	idev->reconnect_timer = g_timeout_add_seconds(30,
					input_device_auto_reconnect, idev);

}