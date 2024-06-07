PHP_FUNCTION(xmlrpc_encode_request)
{
	XMLRPC_REQUEST xRequest = NULL;
	char *outBuf;
	zval *vals, *out_opts = NULL;
	char *method = NULL;
	size_t method_len;
	php_output_options out;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "STR", &method, &method_len, &vals, &out_opts) == FAILURE) {
		return;
	}

	set_output_options(&out, out_opts ? out_opts : 0);

	if (USED_RET()) {
		xRequest = XMLRPC_RequestNew();

		if (xRequest) {
			XMLRPC_RequestSetOutputOptions(xRequest, &out.xmlrpc_out);
			if (method == NULL) {
				XMLRPC_RequestSetRequestType(xRequest, xmlrpc_request_response);
			} else {
				XMLRPC_RequestSetMethodName(xRequest, method);
				XMLRPC_RequestSetRequestType(xRequest, xmlrpc_request_call);
			}
			if (Z_TYPE_P(vals) != IS_NULL) {
				XMLRPC_RequestSetData(xRequest, PHP_to_XMLRPC(vals));
			}

			outBuf = XMLRPC_REQUEST_ToXML(xRequest, 0);
			if (outBuf) {
				RETVAL_STRING(outBuf);
				free(outBuf);
			}
			XMLRPC_RequestFree(xRequest, 1);
		}
	}

	if (strcmp(out.xmlrpc_out.xml_elem_opts.encoding, ENCODING_DEFAULT) != 0) {
		efree((char *)out.xmlrpc_out.xml_elem_opts.encoding);
	}
}