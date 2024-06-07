e_ews_connection_get_attachments (EEwsConnection *cnc,
                                  gint pri,
                                  const gchar *uid,
                                  const GSList *ids,
                                  const gchar *cache,
                                  gboolean include_mime,
                                  ESoapProgressFn progress_fn,
                                  gpointer progress_data,
                                  GCancellable *cancellable,
                                  GAsyncReadyCallback callback,
                                  gpointer user_data)
{
	ESoapMessage *msg;
	GSimpleAsyncResult *simple;
	EwsAsyncData *async_data;
	const GSList *l;

	g_return_if_fail (cnc != NULL);

	msg = e_ews_message_new_with_header (
			cnc->priv->settings,
			cnc->priv->uri,
			cnc->priv->impersonate_user,
			"STR",
			NULL,
			NULL,
			cnc->priv->version,
			E_EWS_EXCHANGE_2007_SP1,
			FALSE,
			TRUE);

	
	if (progress_fn && progress_data)
		e_soap_message_set_progress_fn (msg, progress_fn, progress_data);

	if (cache)
		e_soap_message_store_node_data (msg, "STR", cache, TRUE);

	
	e_soap_message_start_element (msg, "STR", NULL);
	e_ews_message_write_string_parameter (msg, "STR");
	e_soap_message_end_element (msg);

	
	e_soap_message_start_element (msg, "STR", NULL);

	for (l = ids; l != NULL; l = g_slist_next (l))
		e_ews_message_write_string_parameter_with_attribute (msg, "STR", l->data);

	e_soap_message_end_element (msg);

	e_ews_message_write_footer (msg);

	simple = g_simple_async_result_new (
		G_OBJECT (cnc), callback, user_data,
		e_ews_connection_get_attachments);

	async_data = g_new0 (EwsAsyncData, 1);
	async_data->directory = cache;
	async_data->sync_state = (gchar *) uid;
	g_simple_async_result_set_op_res_gpointer (
		simple, async_data, (GDestroyNotify) async_data_free);

	e_ews_connection_queue_request (
		cnc, msg, get_attachments_response_cb,
		pri, cancellable, simple);

	g_object_unref (simple);
}