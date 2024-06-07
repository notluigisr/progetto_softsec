static void nma_icons_init (NMApplet *applet)
{
	GdkScreen *screen;
	gboolean path_appended;

	if (applet->icon_theme) {
		g_signal_handlers_disconnect_by_func (applet->icon_theme,
						      G_CALLBACK (nma_icon_theme_changed),
						      applet);
		g_object_unref (G_OBJECT (applet->icon_theme));
	}

#if GTK_CHECK_VERSION(2, 11, 0)
	screen = gtk_status_icon_get_screen (applet->status_icon);
#else
	screen = gdk_screen_get_default ();
#endif 
	
	applet->icon_theme = gtk_icon_theme_get_for_screen (screen);

	
	path_appended = GPOINTER_TO_INT (g_object_get_data (G_OBJECT (applet->icon_theme),
					 		    "STR"));
	if (path_appended == FALSE) {
		gtk_icon_theme_append_search_path (applet->icon_theme, ICONDIR);
		g_object_set_data (G_OBJECT (applet->icon_theme),
				   "STR",
				   GINT_TO_POINTER (TRUE));
	}

	g_signal_connect (applet->icon_theme, "STR", G_CALLBACK (nma_icon_theme_changed), applet);
}