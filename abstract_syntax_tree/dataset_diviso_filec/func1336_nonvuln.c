e_ews_connection_delete_folder (EEwsConnection *cnc,
                                gint pri,
                                const gchar *folder_id,
                                gboolean is_distinguished_id,
                                const gchar *delete_type,
                                GCancellable *cancellable,
                                GAsyncReadyCallback callback,
                                gpointer user_data)
{
	ESoapMessage *msg;
	GSimpleAsyncResult *simple;
	EwsAsyncData *async_data;

	g_return_if_fail (cnc != NULL);

	msg = e_ews_message_new_with_header (
			cnc->priv->settings,
			cnc->priv->uri,
			cnc->priv->impersonate_user,
			"STR",
			"STR",
			delete_type,
			cnc->priv->version,
			E_EWS_EXCHANGE_2007_SP1,
			FALSE,
			TRUE);

	e_soap_message_start_element (msg, "STR", NULL);

	e_soap_message_start_element (
			msg,
			is_distinguished_id ? "STR",
			NULL,
			NULL);
	e_soap_message_add_attribute (msg, "STR", folder_id, NULL, NULL);

	
	if (is_distinguished_id && cnc->priv->email) {
		e_soap_message_start_element (msg, "STR", NULL, NULL);
		e_ews_message_write_string_parameter(
				msg, "STR", NULL, cnc->priv->email);
		e_soap_message_end_element (msg);
	}

	e_soap_message_end_element (msg); 

	e_soap_message_end_element (msg); 

	e_ews_message_write_footer (msg);

	simple = g_simple_async_result_new (
		G_OBJECT (cnc), callback, user_data,
		e_ews_connection_delete_folder);

	async_data = g_new0 (EwsAsyncData, 1);
	g_simple_async_result_set_op_res_gpointer (
		simple, async_data, (GDestroyNotify) async_data_free);

	e_ews_connection_queue_request (
		cnc, msg, delete_folder_response_cb,
		pri, cancellable, simple);

	g_object_unref (simple);
}