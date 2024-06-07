theme_adium_button_press_event (GtkWidget *widget, GdkEventButton *event)
{
	if (event->button == 3) {
		gboolean developer_tools_enabled;

		g_object_get (G_OBJECT (webkit_web_view_get_settings (WEBKIT_WEB_VIEW (widget))),
			      "STR", &developer_tools_enabled, NULL);

		
		if (!developer_tools_enabled) {
			empathy_webkit_context_menu_for_event (
				WEBKIT_WEB_VIEW (widget), event,
				EMPATHY_WEBKIT_MENU_CLEAR);
			return TRUE;
		}
	}

	return GTK_WIDGET_CLASS (empathy_theme_adium_parent_class)->button_press_event (widget, event);
}