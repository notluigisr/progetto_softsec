open_window (NautilusApplication *application,
	     const char *startup_id,
	     const char *uri, const char *geometry, gboolean browser_window)
{
	GFile *location;
	NautilusWindow *window;

	if (browser_window ||
	    eel_preferences_get_boolean (NAUTILUS_PREFERENCES_ALWAYS_USE_BROWSER)) {
		window = nautilus_application_create_navigation_window (application,
									startup_id,
									gdk_screen_get_default ());
		if (uri == NULL) {
			nautilus_window_go_home (window);
		} else {
			location = g_file_new_for_uri (uri);
			nautilus_window_go_to (window, location);
			g_object_unref (location);
		}
	} else {
		if (uri == NULL) {
			location = g_file_new_for_path (g_get_home_dir ());
		} else {
			location = g_file_new_for_uri (uri);
		}
		
		window = nautilus_application_present_spatial_window (application,
								      NULL,
								      startup_id,
								      location,
								      gdk_screen_get_default ());
		g_object_unref (location);
	}
	
	if (geometry != NULL && !GTK_WIDGET_VISIBLE (window)) {
		
		gtk_window_unmaximize (GTK_WINDOW (window));
		eel_gtk_window_set_initial_geometry_from_string (GTK_WINDOW (window),
								 geometry,
								 APPLICATION_WINDOW_MIN_WIDTH,
								 APPLICATION_WINDOW_MIN_HEIGHT,
								 FALSE);
	}
}