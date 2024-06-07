pk_transaction_install_packages (PkTransaction *transaction,
				 GVariant *params,
				 GDBusMethodInvocation *context)
{
	gboolean ret;
	guint length;
	PkBitfield transaction_flags;
	g_autoptr(GError) error = NULL;
	g_autofree gchar **package_ids = NULL;
	g_autofree gchar *package_ids_temp = NULL;
	g_autofree gchar *transaction_flags_temp = NULL;

	g_return_if_fail (PK_IS_TRANSACTION (transaction));
	g_return_if_fail (transaction->priv->tid != NULL);

	g_variant_get (params, "STR",
		       &transaction_flags,
		       &package_ids);

	package_ids_temp = pk_package_ids_to_string (package_ids);
	transaction_flags_temp = pk_transaction_flag_bitfield_to_string (transaction_flags);
	g_debug ("STR",
		 package_ids_temp, transaction_flags_temp);

	
	if (!pk_backend_is_implemented (transaction->priv->backend,
					PK_ROLE_ENUM_INSTALL_PACKAGES)) {
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
		pk_transaction_set_state (transaction, PK_TRANSACTION_STATE_ERROR);
		goto out;
	}

	
	transaction->priv->cached_transaction_flags = transaction_flags;
	transaction->priv->cached_package_ids = g_strdupv (package_ids);
	pk_transaction_set_role (transaction, PK_ROLE_ENUM_INSTALL_PACKAGES);

	
	pk_transaction_emit_property_changed (transaction,
					      "STR",
					      g_variant_new_uint64 (transaction_flags));

	
	ret = pk_transaction_obtain_authorization (transaction,
						   PK_ROLE_ENUM_INSTALL_PACKAGES,
						   &error);
	if (!ret) {
		pk_transaction_set_state (transaction, PK_TRANSACTION_STATE_ERROR);
		goto out;
	}
out:
	pk_transaction_dbus_return (context, error);
}