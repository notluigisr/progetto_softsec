connection_new_secrets_requested_cb (NMAGConfConnection *connection,
                                     const char *setting_name,
                                     const char **hints,
                                     gboolean ask_user,
                                     DBusGMethodInvocation *context,
                                     gpointer user_data)
{
	NMAGConfSettings *self = NMA_GCONF_SETTINGS (user_data);

	
	g_signal_emit (self,
	               signals[NEW_SECRETS_REQUESTED],
	               0,
	               connection,
	               setting_name,
	               hints,
	               ask_user,
	               context);
}