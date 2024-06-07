nm_8021x_get_secrets (NMDevice *device,
					  NMConnection *connection,
					  NMActiveConnection *active_connection,
					  const char *setting_name,
					  DBusGMethodInvocation *context,
					  NMApplet *applet,
					  GError **error)
{
	GtkWidget *dialog;
	NM8021xInfo *info;

	dialog = nma_wired_dialog_new (applet->glade_file,
								   applet->nm_client,
								   g_object_ref (connection),
								   device);
	if (!dialog) {
		g_set_error (error, NM_SETTINGS_ERROR, NM_SETTINGS_ERROR_INTERNAL_ERROR,
		             "STR",
		             __FILE__, __LINE__, __func__);
		return FALSE;
	}

	info = g_malloc0 (sizeof (NM8021xInfo));
	info->context = context;
	info->applet = applet;
	info->active_connection = active_connection;
	info->dialog = dialog;

	g_signal_connect (dialog, "STR", G_CALLBACK (get_8021x_secrets_cb), info);

	
	g_object_weak_ref (G_OBJECT (active_connection), destroy_8021x_dialog, info);

	gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_widget_realize (dialog);
	gtk_window_present (GTK_WINDOW (dialog));

	return TRUE;
}