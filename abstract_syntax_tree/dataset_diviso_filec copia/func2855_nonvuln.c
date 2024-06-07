PHP_FUNCTION(xmlrpc_server_register_introspection_callback)
{
	zval *method_name, *handle;
	xmlrpc_server_data* server;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "STR", &handle, &method_name) == FAILURE) {
		return;
	}

	if ((server = (xmlrpc_server_data *)zend_fetch_resource(Z_RES_P(handle), "STR", le_xmlrpc_server)) == NULL) {
		RETURN_FALSE;
	}

	if (Z_REFCOUNTED_P(method_name)) {
		Z_ADDREF_P(method_name);
	}
	
	add_zval(&server->introspection_map, NULL, method_name);

	RETURN_TRUE;
}