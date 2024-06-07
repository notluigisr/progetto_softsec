e_ews_connection_get_server_time_zones (EEwsConnection *cnc,
					gint pri,
					GSList *msdn_locations,
					GCancellable *cancellable,
					GAsyncReadyCallback callback,
					gpointer user_data)
{
	ESoapMessage *msg;
	GSimpleAsyncResult *simple;
	EwsAsyncData *async_data;
	GSList *l;

	g_return_if_fail (cnc != NULL);
	g_return_if_fail (cnc->priv != NULL);

	simple = g_simple_async_result_new (
		G_OBJECT (cnc), callback, user_data, e_ews_connection_get_server_time_zones);
	async_data = g_new0 (EwsAsyncData, 1);
	g_simple_async_result_set_op_res_gpointer (simple, async_data, (GDestroyNotify) async_data_free);

	
	if (!e_ews_connection_satisfies_server_version (cnc, E_EWS_EXCHANGE_2010_SP1)) {
		g_simple_async_result_complete_in_idle (simple);
		g_object_unref (simple);
		return;
	}

	msg = e_ews_message_new_with_header (
		cnc->priv->settings,
		cnc->priv->uri,
		cnc->priv->impersonate_user,
		"STR",
		"STR",
		"STR",
		cnc->priv->version,
		E_EWS_EXCHANGE_2010,
		FALSE,
		TRUE);

	e_soap_message_start_element (msg, "STR", NULL);
	for (l = msdn_locations; l != NULL; l = l->next)
		e_ews_message_write_string_parameter_with_attribute (msg, "STR", NULL, l->data, NULL, NULL);
	e_soap_message_end_element (msg); 

	e_ews_message_write_footer (msg); 

	e_ews_connection_queue_request (cnc, msg, get_server_time_zones_response_cb, pri, cancellable, simple);

	g_object_unref (simple);
}