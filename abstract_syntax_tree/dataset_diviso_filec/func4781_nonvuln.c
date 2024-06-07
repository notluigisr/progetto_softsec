fr_window_get_password (FrWindow *window)
{
	g_return_val_if_fail (window != NULL, NULL);

	return window->priv->password;
}