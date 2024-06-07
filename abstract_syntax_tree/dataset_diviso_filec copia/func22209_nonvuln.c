fr_window_copy_or_cut_selection (FrWindow      *window,
				 FrClipboardOp  op,
			  	 gboolean       from_sidebar)
{
	GList        *files;
	char         *base_dir;
	GtkClipboard *clipboard;

	files = fr_window_get_selection (window, from_sidebar, &base_dir);

	if (window->priv->copy_data != NULL)
		fr_clipboard_data_unref (window->priv->copy_data);
	window->priv->copy_data = fr_clipboard_data_new ();
	window->priv->copy_data->files = files;
	window->priv->copy_data->op = op;
	window->priv->copy_data->base_dir = base_dir;

	clipboard = gtk_clipboard_get (FR_CLIPBOARD);
	gtk_clipboard_set_with_owner (clipboard,
				      clipboard_targets,
				      G_N_ELEMENTS (clipboard_targets),
				      fr_clipboard_get,
				      fr_clipboard_clear,
				      G_OBJECT (window));

	fr_window_update_sensitivity (window);
}