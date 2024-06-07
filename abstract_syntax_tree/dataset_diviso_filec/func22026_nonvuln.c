static PHP_FUNCTION(session_save_path)
{
	char *name = NULL;
	int name_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR", &name, &name_len) == FAILURE) {
		return;
	}

	RETVAL_STRING(PS(save_path), 1);

	if (name) {
		if (memchr(name, '\0', name_len) != NULL) {
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR");
			zval_dtor(return_value);
			RETURN_FALSE;
		}
		zend_alter_ini_entry("STR"), name, name_len, PHP_INI_USER, PHP_INI_STAGE_RUNTIME);
	}
}