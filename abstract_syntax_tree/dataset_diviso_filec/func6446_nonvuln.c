nautilus_application_close_parent_windows (NautilusSpatialWindow *window)
{
	NautilusSpatialWindow *parent_window;
	NautilusSpatialWindow *new_parent_window;

	g_return_if_fail (NAUTILUS_IS_SPATIAL_WINDOW (window));

	parent_window = find_parent_spatial_window (window);
	
	while (parent_window) {
		
		new_parent_window = find_parent_spatial_window (parent_window);
		nautilus_window_close (NAUTILUS_WINDOW (parent_window));
		parent_window = new_parent_window;
	}
}