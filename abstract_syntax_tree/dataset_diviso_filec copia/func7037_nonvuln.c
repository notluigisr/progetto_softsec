applet_is_any_device_activating (NMApplet *applet)
{
	const GPtrArray *devices;
	int i;

	
	devices = nm_client_get_devices (applet->nm_client);
	for (i = 0; devices && (i < devices->len); i++) {
		NMDevice *candidate = NM_DEVICE (g_ptr_array_index (devices, i));
		NMDeviceState state;

		state = nm_device_get_state (candidate);
		if (state > NM_DEVICE_STATE_DISCONNECTED && state < NM_DEVICE_STATE_ACTIVATED)
			return TRUE;
	}
	return FALSE;
}