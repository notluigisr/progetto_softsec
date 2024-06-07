imapx_disconnect (CamelIMAPXServer *is)
{
	g_cancellable_cancel (is->priv->cancellable);

	g_mutex_lock (&is->priv->stream_lock);

	if (is->priv->connection) {
		
		imapx_server_set_connection_timeout (is->priv->connection, 3);
	}

	g_clear_object (&is->priv->input_stream);
	g_clear_object (&is->priv->output_stream);
	g_clear_object (&is->priv->connection);
	g_clear_object (&is->priv->subprocess);

	if (is->priv->cinfo) {
		imapx_free_capability (is->priv->cinfo);
		is->priv->cinfo = NULL;
	}

	g_mutex_unlock (&is->priv->stream_lock);

	g_mutex_lock (&is->priv->select_lock);
	is->priv->last_selected_mailbox_change_stamp = 0;
	g_weak_ref_set (&is->priv->select_mailbox, NULL);
	g_weak_ref_set (&is->priv->select_pending, NULL);
	g_mutex_unlock (&is->priv->select_lock);

	is->priv->is_cyrus = FALSE;
	is->priv->is_broken_cyrus = FALSE;
	is->priv->state = IMAPX_DISCONNECTED;

	g_mutex_lock (&is->priv->idle_lock);
	is->priv->idle_state = IMAPX_IDLE_STATE_OFF;
	g_cond_broadcast (&is->priv->idle_cond);
	g_mutex_unlock (&is->priv->idle_lock);
}