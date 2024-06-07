fr_window_archive_is_present (FrWindow *window)
{
	g_return_val_if_fail (window != NULL, FALSE);

	return window->priv->archive_present;
}