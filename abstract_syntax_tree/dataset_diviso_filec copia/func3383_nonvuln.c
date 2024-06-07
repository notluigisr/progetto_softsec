e_ews_connection_get_ssl_error_details (EEwsConnection *cnc,
					gchar **out_certificate_pem,
					GTlsCertificateFlags *out_certificate_errors)
{
	g_return_val_if_fail (E_IS_EWS_CONNECTION (cnc), FALSE);
	g_return_val_if_fail (out_certificate_pem != NULL, FALSE);
	g_return_val_if_fail (out_certificate_errors != NULL, FALSE);

	g_mutex_lock (&cnc->priv->property_lock);
	if (!cnc->priv->ssl_info_set) {
		g_mutex_unlock (&cnc->priv->property_lock);
		return FALSE;
	}

	*out_certificate_pem = g_strdup (cnc->priv->ssl_certificate_pem);
	*out_certificate_errors = cnc->priv->ssl_certificate_errors;

	g_mutex_unlock (&cnc->priv->property_lock);

	return TRUE;
}