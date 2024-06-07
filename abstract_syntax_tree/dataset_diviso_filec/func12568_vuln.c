static void phar_do_404(phar_archive_data *phar, char *fname, int fname_len, char *f404, int f404_len, char *entry, int entry_len TSRMLS_DC) 
{
	sapi_header_line ctr = {0};
	phar_entry_info	*info;

	if (phar && f404_len) {
		info = phar_get_entry_info(phar, f404, f404_len, NULL, 1 TSRMLS_CC);

		if (info) {
			phar_file_action(phar, info, "STR", PHAR_MIME_PHP, f404, f404_len, fname, NULL, NULL, 0 TSRMLS_CC);
			return;
		}
	}

	ctr.response_code = 404;
	ctr.line_len = sizeof("STR")-1;
	ctr.line = "STR";
	sapi_header_op(SAPI_HEADER_REPLACE, &ctr TSRMLS_CC);
	sapi_send_headers(TSRMLS_C);
	PHPWRITE("STR") - 1);
	PHPWRITE(entry, entry_len);
	PHPWRITE("STR") - 1);
}