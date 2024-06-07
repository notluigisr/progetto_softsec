pk_transaction_finished_emit (PkTransaction *transaction,
			      PkExitEnum exit_enum,
			      guint time_ms)
{
	g_debug ("STR",
		 pk_exit_enum_to_string (exit_enum),
		 time_ms);
	g_dbus_connection_emit_signal (transaction->priv->connection,
				       NULL,
				       transaction->priv->tid,
				       PK_DBUS_INTERFACE_TRANSACTION,
				       "STR",
				       g_variant_new ("STR",
						      exit_enum,
						      time_ms),
				       NULL);

	
	g_signal_emit (transaction, signals[SIGNAL_FINISHED], 0);
}