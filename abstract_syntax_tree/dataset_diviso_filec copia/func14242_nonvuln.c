pk_transaction_download_packages (PkTransaction *transaction,
				  GVariant *params,
				  GDBusMethodInvocation *context)
{
	gboolean ret;
	gint retval;
	guint length;
	gboolean store_in_cache;
	gchar **package_ids = NULL;
	_cleanup_error_free_ GError *error = NULL;
	_cleanup_free_ gchar *directory = NULL;
	_cleanup_free_ gchar *package_ids_temp = NULL;

	g_return_if_fail (PK_IS_TRANSACTION (transaction));
	g_return_if_fail (transaction->priv->tid != NULL);

	g_variant_get (params, "STR",
		       &store_in_cache,
		       &package_ids);

	package_ids_temp = pk_package_ids_to_string (package_ids);
	g_debug ("STR", package_ids_temp);

	
	if (!pk_backend_is_implemented (transaction->priv->backend,
					PK_ROLE_ENUM_DOWNLOAD_PACKAGES)) {
		g_set_error (&error,
			     PK_TRANSACTION_ERROR,
			     PK_TRANSACTION_ERROR_NOT_SUPPORTED,
			     "STR");
		pk_transaction_set_state (transaction, PK_TRANSACTION_STATE_ERROR);
		goto out;
	}

	
	length = g_strv_length (package_ids);
	if (length > PK_TRANSACTION_MAX_PACKAGES_TO_PROCESS) {
		g_set_error (&error,
			     PK_TRANSACTION_ERROR,
			     PK_TRANSACTION_ERROR_NUMBER_OF_PACKAGES_INVALID,
			     "STR",
			     length, PK_TRANSACTION_MAX_PACKAGES_TO_PROCESS);
		pk_transaction_set_state (transaction, PK_TRANSACTION_STATE_ERROR);
		goto out;
	}

	
	ret = pk_package_ids_check (package_ids);
	if (!ret) {
		g_set_error (&error,
			     PK_TRANSACTION_ERROR,
			     PK_TRANSACTION_ERROR_PACKAGE_ID_INVALID,
			     "STR", package_ids_temp);
		goto out;
	}

	
	if (!store_in_cache) {
		directory = g_build_filename (LOCALSTATEDIR, "STR",
					     "STR", transaction->priv->tid, NULL);
		
		retval = g_mkdir (directory, 0775);
		if (retval != 0) {
			g_set_error (&error,
				     PK_TRANSACTION_ERROR,
				     PK_TRANSACTION_ERROR_DENIED,
				     "STR", directory);
			goto out;
		}
	}

	
	transaction->priv->cached_package_ids = g_strdupv (package_ids);
	transaction->priv->cached_directory = g_strdup (directory);
	pk_transaction_set_role (transaction, PK_ROLE_ENUM_DOWNLOAD_PACKAGES);
	pk_transaction_set_state (transaction, PK_TRANSACTION_STATE_READY);
out:
	pk_transaction_dbus_return (context, error);
}