int highlight_file(char *filename, zend_syntax_highlighter_ini *syntax_highlighter_ini TSRMLS_DC)
{
	zend_lex_state original_lex_state;
	zend_file_handle file_handle;

	file_handle.type = ZEND_HANDLE_FILENAME;
	file_handle.filename = filename;
	file_handle.free_filename = 0;
	file_handle.opened_path = NULL;
	zend_save_lexical_state(&original_lex_state TSRMLS_CC);
	if (open_file_for_scanning(&file_handle TSRMLS_CC)==FAILURE) {
		zend_message_dispatcher(ZMSG_FAILED_HIGHLIGHT_FOPEN, filename TSRMLS_CC);
		zend_restore_lexical_state(&original_lex_state TSRMLS_CC);
		return FAILURE;
	}
	zend_highlight(syntax_highlighter_ini TSRMLS_CC);
	if (SCNG(script_filtered)) {
		efree(SCNG(script_filtered));
		SCNG(script_filtered) = NULL;
	}
	zend_destroy_file_handle(&file_handle TSRMLS_CC);
	zend_restore_lexical_state(&original_lex_state TSRMLS_CC);
	return SUCCESS;
}