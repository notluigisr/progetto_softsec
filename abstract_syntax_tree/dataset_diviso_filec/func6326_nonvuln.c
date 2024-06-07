nautilus_application_close_all_navigation_windows (void)
{
	GList *list_copy;
	GList *l;
	
	list_copy = g_list_copy (nautilus_application_window_list);
	for (l = list_copy; l != NULL; l = l->next) {
		NautilusWindow *window;
		
		window = NAUTILUS_WINDOW (l->data);
		
		if (NAUTILUS_IS_NAVIGATION_WINDOW (window)) {
			nautilus_window_close (window);
		}
	}
	g_list_free (list_copy);
}