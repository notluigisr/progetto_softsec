pk_transaction_resolve (PkTransaction *transaction,
			GVariant *params,
			GDBusMethodInvocation *context)
{
	gboolean ret;
	guint i;
	guint length;
	PkBitfield filter;
	gchar **packages;
	_cleanup_error_free_ GError *error = NULL;
	_cleanup_free_ gchar *packages_temp = NULL;

	g_return_if_fail (PK_IS_TRANSACTION (transaction));
	g_return_if_fail (transaction->priv->tid != NULL);

	g_variant_get (params, "STR",
		       &filter,
		       &packages);

	packages_temp = pk_package_ids_to_string (packages);
	g_debug ("STR",
		 filter, packages_temp);

	
	if (!pk_backend_is_implemented (transaction->priv->backend,
					PK_ROLE_ENUM_RESOLVE)) {
		g_set_error (&error,
			     PK_TRANSACTION_ERROR,
			     PK_TRANSACTION_ERROR_NOT_SUPPORTED,
			     "STR");
		pk_transaction_set_state (transaction, PK_TRANSACTION_STATE_ERROR);
		goto out;
	}

	
	length = g_strv_length (packages);
	if (length == 0) {
		g_set_error (&error,
			     PK_TRANSACTION_ERROR,
			     PK_TRANSACTION_ERROR_INPUT_INVALID,
			     "STR");
		pk_transaction_set_state (transaction, PK_TRANSACTION_STATE_ERROR);
		goto out;
	}
	if (length > PK_TRANSACTION_MAX_ITEMS_TO_RESOLVE) {
		g_set_error (&error,
			     PK_TRANSACTION_ERROR,
			     PK_TRANSACTION_ERROR_INPUT_INVALID,
			     "STR",
			     length, PK_TRANSACTION_MAX_ITEMS_TO_RESOLVE);
		pk_transaction_set_state (transaction, PK_TRANSACTION_STATE_ERROR);
		goto out;
	}

	
	for (i = 0; i < length; i++) {
		ret = pk_transaction_strvalidate (packages[i], &error);
		if (!ret) {
			pk_transaction_set_state (transaction, PK_TRANSACTION_STATE_ERROR);
			goto out;
		}
	}

	
	transaction->priv->cached_package_ids = g_strdupv (packages);
	transaction->priv->cached_filters = filter;
	pk_transaction_set_role (transaction, PK_ROLE_ENUM_RESOLVE);
	pk_transaction_set_state (transaction, PK_TRANSACTION_STATE_READY);
out:
	pk_transaction_dbus_return (context, error);
}