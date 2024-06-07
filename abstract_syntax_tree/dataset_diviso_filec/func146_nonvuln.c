wireless_device_added (NMDevice *device, NMApplet *applet)
{
	NMDeviceWifi *wdev = NM_DEVICE_WIFI (device);
	const GPtrArray *aps;
	int i;
	struct ap_notification_data *data;
	guint id;

	g_signal_connect (wdev,
	                  "STR" NM_DEVICE_WIFI_ACTIVE_ACCESS_POINT,
	                  G_CALLBACK (notify_active_ap_changed_cb),
	                  applet);

	g_signal_connect (wdev,
	                  "STR",
	                  G_CALLBACK (access_point_added_cb),
	                  applet);

	g_signal_connect (wdev,
	                  "STR",
	                  G_CALLBACK (access_point_removed_cb),
	                  applet);

	
	data = g_new0 (struct ap_notification_data, 1);
	data->applet = applet;
	data->device = wdev;
	 
	id = g_signal_connect (applet_get_settings (applet), "STR",
	                       G_CALLBACK (on_new_connection),
	                       data);
	data->new_con_id = id;
	g_object_set_data_full (G_OBJECT (wdev), "STR",
	                        data, free_ap_notification_data);

	queue_avail_access_point_notification (device);

	
	aps = nm_device_wifi_get_access_points (wdev);
	for (i = 0; aps && (i < aps->len); i++)
		add_hash_to_ap (g_ptr_array_index (aps, i));
}