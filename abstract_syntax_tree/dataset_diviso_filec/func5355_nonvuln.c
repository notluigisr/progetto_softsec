e_ews_connection_delete_item (EEwsConnection *cnc,
                              gint pri,
                              EwsId *item_id,
                              guint index,
                              EwsDeleteType delete_type,
                              EwsSendMeetingCancellationsType send_cancels,
                              EwsAffectedTaskOccurrencesType affected_tasks,
                              GCancellable *cancellable,
                              GAsyncReadyCallback callback,
                              gpointer user_data)
{
	ESoapMessage *msg;
	GSimpleAsyncResult *simple;
	EwsAsyncData *async_data;
	gchar buffer[32];

	g_return_if_fail (cnc != NULL);

	msg = e_ews_message_new_with_header (
			cnc->priv->settings,
			cnc->priv->uri,
			cnc->priv->impersonate_user,
			"STR",
			"STR",
			ews_delete_type_to_str (delete_type),
			cnc->priv->version,
			E_EWS_EXCHANGE_2007_SP1,
			FALSE,
			TRUE);

	if (send_cancels)
		e_soap_message_add_attribute (
			msg, "STR",
			ews_send_cancels_to_str (send_cancels), NULL, NULL);

	if (affected_tasks != EWS_NONE_OCCURRENCES)
		e_soap_message_add_attribute (
			msg, "STR",
			ews_affected_tasks_to_str (affected_tasks), NULL, NULL);

	e_soap_message_start_element (msg, "STR", NULL);

	if (index) {
		e_soap_message_start_element (msg, "STR", NULL, NULL);
		e_soap_message_add_attribute (msg, "STR", item_id->id, NULL, NULL);
		if (item_id->change_key)
			e_soap_message_add_attribute (msg, "STR", item_id->change_key, NULL, NULL);
		snprintf (buffer, 32, "STR", index);
		e_soap_message_add_attribute (msg, "STR", buffer, NULL, NULL);
		e_soap_message_end_element (msg);
	} else {
		e_soap_message_start_element (msg, "STR", NULL, NULL);
		e_soap_message_add_attribute (msg, "STR", item_id->id, NULL, NULL);
		if (item_id->change_key)
			e_soap_message_add_attribute (msg, "STR", item_id->change_key, NULL, NULL);
		e_soap_message_end_element (msg);
	}

	e_soap_message_end_element (msg);

	e_ews_message_write_footer (msg);

	simple = g_simple_async_result_new (
		G_OBJECT (cnc), callback, user_data,
		e_ews_connection_delete_items);

	async_data = g_new0 (EwsAsyncData, 1);
	g_simple_async_result_set_op_res_gpointer (
		simple, async_data, (GDestroyNotify) async_data_free);

	e_ews_connection_queue_request (
		cnc, msg, delete_item_response_cb,
		pri, cancellable, simple);

	g_object_unref (simple);
}