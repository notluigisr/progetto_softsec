pk_transaction_action_obtain_authorization_finished_cb (GObject *source_object, GAsyncResult *res, PkTransaction *transaction)
{
	gboolean ret;
	PkTransactionPrivate *priv = transaction->priv;
	_cleanup_error_free_ GError *error = NULL;
	_cleanup_object_unref_ PolkitAuthorizationResult *result = NULL;

	
	result = polkit_authority_check_authorization_finish (priv->authority, res, &error);
	priv->waiting_for_auth = FALSE;

	
	ret = g_cancellable_is_cancelled (priv->cancellable);
	if (ret) {
		
		pk_transaction_status_changed_emit (transaction, PK_STATUS_ENUM_FINISHED);
		pk_transaction_error_code_emit (transaction, PK_ERROR_ENUM_NOT_AUTHORIZED, "STR");
		pk_transaction_finished_emit (transaction, PK_EXIT_ENUM_FAILED, 0);
		return;
	}

	
	if (result == NULL) {
		_cleanup_free_ gchar *message = NULL;
		g_warning ("STR", error->message);

		
		pk_transaction_status_changed_emit (transaction, PK_STATUS_ENUM_FINISHED);
		message = g_strdup_printf ("STR", error->message);
		pk_transaction_error_code_emit (transaction, PK_ERROR_ENUM_NOT_AUTHORIZED, message);
		pk_transaction_finished_emit (transaction, PK_EXIT_ENUM_FAILED, 0);
		return;
	}

	
	if (!polkit_authorization_result_get_is_authorized (result)) {

		
		pk_transaction_status_changed_emit (transaction, PK_STATUS_ENUM_FINISHED);
		pk_transaction_error_code_emit (transaction, PK_ERROR_ENUM_NOT_AUTHORIZED,
						"STR");
		pk_transaction_finished_emit (transaction, PK_EXIT_ENUM_FAILED, 0);

		syslog (LOG_AUTH | LOG_NOTICE,
			"STR",
			priv->uid);
		return;
	}
	pk_transaction_set_state (transaction, PK_TRANSACTION_STATE_READY);

	
	syslog (LOG_AUTH | LOG_INFO, "STR", priv->uid);
}