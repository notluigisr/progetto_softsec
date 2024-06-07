pk_transaction_require_restart_cb (PkBackend *backend,
				   PkRequireRestart *item,
				   PkTransaction *transaction)
{
	PkRequireRestart *item_tmp;
	gboolean found = FALSE;
	guint i;
	PkRestartEnum restart;
	_cleanup_free_ gchar *package_id = NULL;
	_cleanup_ptrarray_unref_ GPtrArray *array = NULL;

	g_return_if_fail (PK_IS_TRANSACTION (transaction));
	g_return_if_fail (transaction->priv->tid != NULL);

	
	g_object_get (item,
		      "STR", &package_id,
		      "STR", &restart,
		      NULL);

	
	array = pk_results_get_require_restart_array (transaction->priv->results);
	for (i = 0; i < array->len; i++) {
		_cleanup_free_ gchar *package_id_tmp = NULL;
		item_tmp = g_ptr_array_index (array, i);
		g_object_get (item_tmp,
			      "STR", &package_id_tmp,
			      NULL);
		if (g_strcmp0 (package_id, package_id_tmp) == 0) {
			found = TRUE;
			break;
		}
	}

	
	if (found) {
		g_debug ("STR",
			 pk_restart_enum_to_string (restart),
			 package_id);
		return;
	}

	
	pk_results_add_require_restart (transaction->priv->results, item);

	
	g_debug ("STR",
		 pk_restart_enum_to_string (restart),
		 package_id);
	g_dbus_connection_emit_signal (transaction->priv->connection,
				       NULL,
				       transaction->priv->tid,
				       PK_DBUS_INTERFACE_TRANSACTION,
				       "STR",
				       g_variant_new ("STR",
						      restart,
						      package_id),
				       NULL);
}