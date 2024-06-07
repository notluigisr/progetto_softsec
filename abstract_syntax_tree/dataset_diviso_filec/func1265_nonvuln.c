ews_connection_write_only_ids_restriction (ESoapMessage *msg,
					   GPtrArray *only_ids)
{
	guint ii;

	g_return_if_fail (E_IS_SOAP_MESSAGE (msg));
	g_return_if_fail (only_ids && only_ids->len);

	for (ii = 0; ii < only_ids->len; ii++) {
		const gchar *itemid = g_ptr_array_index (only_ids, ii);

		e_soap_message_start_element (msg, "STR", NULL, NULL);
		e_ews_message_write_string_parameter_with_attribute (msg, "STR");
		e_soap_message_start_element (msg, "STR", NULL, NULL);
		e_ews_message_write_string_parameter_with_attribute (msg, "STR", itemid);
		e_soap_message_end_element (msg); 
		e_soap_message_end_element (msg); 
	}
}