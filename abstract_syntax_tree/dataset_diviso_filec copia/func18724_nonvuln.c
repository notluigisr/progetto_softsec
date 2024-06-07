activity_cb (gpointer data)
{
	FrWindow *window = data;

	if ((window->priv->pd_progress_bar != NULL) && window->priv->progress_pulse)
		gtk_progress_bar_pulse (GTK_PROGRESS_BAR (window->priv->pd_progress_bar));
	if (window->priv->progress_pulse)
		gtk_progress_bar_pulse (GTK_PROGRESS_BAR (window->priv->progress_bar));

	return TRUE;
}