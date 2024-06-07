wireless_get_more_info (NMDevice *device,
                        NMConnection *connection,
                        NMApplet *applet,
                        gpointer user_data)
{
	WirelessMenuItemInfo *info = (WirelessMenuItemInfo *) user_data;
	GtkWidget *dialog;

	dialog = nma_wireless_dialog_new (applet, connection, device, info->ap);
	g_return_if_fail (dialog != NULL);

	g_signal_connect (dialog, "STR",
	                  G_CALLBACK (wireless_dialog_response_cb),
	                  applet);

	show_ignore_focus_stealing_prevention (dialog);
}