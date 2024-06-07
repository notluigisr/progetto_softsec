book_backend_ldap_refresh_sync (EBookBackend *backend,
				GCancellable *cancellable,
				GError **error)
{
	EBookBackendLDAP *ldap_backend = E_BOOK_BACKEND_LDAP (backend);

	g_return_val_if_fail (ldap_backend != NULL, FALSE);
	g_return_val_if_fail (ldap_backend->priv != NULL, FALSE);

	if (!ldap_backend->priv->cache || !ldap_backend->priv->marked_for_offline ||
	    ldap_backend->priv->generate_cache_in_progress)
		return TRUE;

	e_book_backend_cache_set_time (ldap_backend->priv->cache, "");
	generate_cache (ldap_backend);

	return TRUE;
}