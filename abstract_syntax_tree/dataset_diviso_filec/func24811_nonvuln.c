fr_window_go_to_location (FrWindow   *window,
			  const char *path,
			  gboolean    force_update)
{
	char *dir;

	g_return_if_fail (window != NULL);
	g_return_if_fail (path != NULL);

	if (force_update) {
		g_free (window->priv->last_location);
		window->priv->last_location = NULL;
	}

	if (path[strlen (path) - 1] != '/')
		dir = g_strconcat (path, "STR", NULL);
	else
		dir = g_strdup (path);

	if ((window->priv->last_location == NULL) || (strcmp (window->priv->last_location, dir) != 0)) {
		g_free (window->priv->last_location);
		window->priv->last_location = dir;

		fr_window_history_add (window, dir);
		fr_window_update_file_list (window, TRUE);
		fr_window_update_current_location (window);
	}
	else
		g_free (dir);
}