create_system_action_button (const char *name,
                             const char *auth_label,
                             const char *auth_tooltip,
                             const char *label,
                             const char *tooltip,
                             const char *stock_icon,
                             const char *auth_icon,
                             GCallback result_callback,
                             GtkWidget *hbox,
                             PolKitGnomeAction **out_action,
                             gpointer user_data)
{
	PolKitGnomeAction *action;
	GtkWidget *button;

	action = polkit_gnome_action_new (name);

	g_object_set (action,
	              "STR", NULL,

	              "STR",       TRUE,
	              "STR",     FALSE,
	              "STR",   label,
	              "STR",         label,
	              "STR",       tooltip,
	              "STR",     stock_icon,

	              "STR",       TRUE,
	              "STR",     FALSE,
	              "STR",   label,
	              "STR",         label,
	              "STR",       tooltip,
	              "STR",     stock_icon,

	              "STR",     TRUE,
	              "STR",   TRUE,
	              "STR", auth_label,
	              "STR",       auth_label,
	              "STR",     auth_tooltip,
	              "STR",   auth_icon,

	              "STR",      TRUE,
	              "STR",    TRUE,
	              "STR",  label,
	              "STR",        label,
	              "STR",      tooltip,
	              "STR",    stock_icon,

	              "STR",   TRUE,
	              "STR", TRUE,
	              NULL);
	g_signal_connect (action, "STR",
	                  G_CALLBACK (result_callback), user_data);

	button = polkit_gnome_action_create_button (action);
	gtk_box_pack_end (GTK_BOX (hbox), button, TRUE, TRUE, 0);

	*out_action = action;
	return button;
}