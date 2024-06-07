notification_closed_cb  (NotifyNotification *notification,
			 gpointer            user_data)
{
	NotifyData *notify_data = user_data;
	FrWindow   *window = notify_data->window;

	if (! notify_data->window_closed)
		gtk_window_present (GTK_WINDOW (window->priv->progress_dialog));

	g_free (notify_data);
}