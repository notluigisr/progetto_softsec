e_ews_connection_get_mailbox (EEwsConnection *cnc)
{
	g_return_val_if_fail (E_IS_EWS_CONNECTION (cnc), NULL);

	if (!cnc->priv->email || !*cnc->priv->email)
		return camel_ews_settings_get_email (cnc->priv->settings);

	return cnc->priv->email;
}