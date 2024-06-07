finish_startup (NautilusApplication *application)
{
	GList *drives;

	
	nautilus_module_setup ();

	
	menu_provider_init_callback ();
	
	
	nautilus_desktop_link_monitor_get ();

	

	
	
	application->volume_monitor = g_volume_monitor_get ();
	g_signal_connect_object (application->volume_monitor, "STR",
				 G_CALLBACK (mount_removed_callback), application, 0);
	g_signal_connect_object (application->volume_monitor, "STR",
				 G_CALLBACK (mount_removed_callback), application, 0);
	g_signal_connect_object (application->volume_monitor, "STR",
				 G_CALLBACK (mount_added_callback), application, 0);
	g_signal_connect_object (application->volume_monitor, "STR",
				 G_CALLBACK (volume_added_callback), application, 0);
	g_signal_connect_object (application->volume_monitor, "STR",
				 G_CALLBACK (drive_connected_callback), application, 0);

	
	drives = g_volume_monitor_get_connected_drives (application->volume_monitor);
	g_list_foreach (drives, (GFunc) drive_listen_for_eject_button, application);
	g_list_foreach (drives, (GFunc) g_object_unref, NULL);
	g_list_free (drives);

	application->automount_idle_id = 
		g_idle_add_full (G_PRIORITY_LOW,
				 automount_all_volumes_idle_cb,
				 application, NULL);
}