static void phar_do_403(char *entry, int entry_len TSRMLS_DC) 
{
	sapi_header_line ctr = {0};

	ctr.response_code = 403;
	ctr.line_len = sizeof("STR")-1;
	ctr.line = "STR";
	sapi_header_op(SAPI_HEADER_REPLACE, &ctr TSRMLS_CC);
	sapi_send_headers(TSRMLS_C);
	PHPWRITE("STR") - 1);
	PHPWRITE(entry, entry_len);
	PHPWRITE("STR") - 1);
}