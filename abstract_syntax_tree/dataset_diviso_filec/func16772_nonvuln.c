delete_item_response_cb (ESoapResponse *response,
                         GSimpleAsyncResult *simple)
{
	ESoapParameter *param;
	ESoapParameter *subparam;
	GError *error = NULL;

	param = e_soap_response_get_first_parameter_by_name (
		response, "STR", &error);

	
	g_return_if_fail (
		(param != NULL && error == NULL) ||
		(param == NULL && error != NULL));

	if (error != NULL) {
		g_simple_async_result_take_error (simple, error);
		return;
	}

	subparam = e_soap_parameter_get_first_child (param);

	while (subparam != NULL) {
		if (!ews_get_response_status (subparam, &error)) {
			g_simple_async_result_take_error (simple, error);
			return;
		}

		subparam = e_soap_parameter_get_next_child (subparam);
	}
}