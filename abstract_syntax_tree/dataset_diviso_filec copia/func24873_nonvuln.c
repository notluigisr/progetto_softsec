nm_gconf_compare_private_connection_values (NMConnection *dst, NMConnection *src)
{
	gboolean val1, val2;

	g_return_val_if_fail (NM_IS_CONNECTION (dst), FALSE);
	g_return_val_if_fail (NM_IS_CONNECTION (src), FALSE);

	val1 = !!GPOINTER_TO_UINT (g_object_get_data (G_OBJECT (src), NMA_CA_CERT_IGNORE_TAG));
	val2 = !!GPOINTER_TO_UINT (g_object_get_data (G_OBJECT (dst), NMA_CA_CERT_IGNORE_TAG));
	if (val1 != val2)
		return FALSE;

	val1 = !!GPOINTER_TO_UINT (g_object_get_data (G_OBJECT (src), NMA_PHASE2_CA_CERT_IGNORE_TAG));
	val2 = !!GPOINTER_TO_UINT (g_object_get_data (G_OBJECT (dst), NMA_PHASE2_CA_CERT_IGNORE_TAG));
	if (val1 != val2)
		return FALSE;

	if (!string_compare (src, dst, NMA_PATH_CLIENT_CERT_TAG))
		return FALSE;
	if (!string_compare (src, dst, NMA_PATH_PHASE2_CLIENT_CERT_TAG))
		return FALSE;
	if (!string_compare (src, dst, NMA_PATH_CA_CERT_TAG))
		return FALSE;
	if (!string_compare (src, dst, NMA_PATH_PHASE2_CA_CERT_TAG))
		return FALSE;
	if (!string_compare (src, dst, NMA_PATH_PRIVATE_KEY_TAG))
		return FALSE;
	if (!string_compare (src, dst, NMA_PRIVATE_KEY_PASSWORD_TAG))
		return FALSE;
	if (!string_compare (src, dst, NMA_PATH_PHASE2_PRIVATE_KEY_TAG))
		return FALSE;
	if (!string_compare (src, dst, NMA_PHASE2_PRIVATE_KEY_PASSWORD_TAG))
		return FALSE;

	return TRUE;
}