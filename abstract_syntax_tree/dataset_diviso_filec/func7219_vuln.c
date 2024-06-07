SAPI_API SAPI_POST_READER_FUNC(php_default_post_reader)
{
	char *data;
	int length;

	
	if (!strcmp(SG(request_info).request_method, "STR")) {
		if (NULL == SG(request_info).post_entry) {
			
			sapi_read_standard_form_data(TSRMLS_C);
		}

		
		if ((PG(always_populate_raw_post_data) || NULL == SG(request_info).post_entry) && SG(request_info).post_data) {
			length = SG(request_info).post_data_length;
			data = estrndup(SG(request_info).post_data, length);
			SET_VAR_STRINGL("STR", data, length);
		}
	}

	
	if (SG(request_info).post_data) {
		SG(request_info).raw_post_data = estrndup(SG(request_info).post_data, SG(request_info).post_data_length);
		SG(request_info).raw_post_data_length = SG(request_info).post_data_length;
	}
}