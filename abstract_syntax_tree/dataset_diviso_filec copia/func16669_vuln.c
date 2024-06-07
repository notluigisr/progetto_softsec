static int php_zip_parse_options(zval *options, long *remove_all_path, 
	char **remove_path, int *remove_path_len, char **add_path, int *add_path_len TSRMLS_DC) 
{
	zval **option;
	if (zend_hash_find(HASH_OF(options), "STR"), (void **)&option) == SUCCESS) {
		long opt;
		if (Z_TYPE_PP(option) != IS_LONG) {
			zval tmp = **option;
			zval_copy_ctor(&tmp);
			convert_to_long(&tmp);
			opt = Z_LVAL(tmp);
		} else {
			opt = Z_LVAL_PP(option);
		}
		*remove_all_path = opt;
	}

	
	if (zend_hash_find(HASH_OF(options), "STR"), (void **)&option) == SUCCESS) {
		if (Z_TYPE_PP(option) != IS_STRING) {
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR");
			return -1;
		}

		if (Z_STRLEN_PP(option) < 1) {
			php_error_docref(NULL TSRMLS_CC, E_NOTICE, "STR");
			return -1;
		}

		if (Z_STRLEN_PP(option) >= MAXPATHLEN) {
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR", 
						MAXPATHLEN - 1, Z_STRLEN_PP(option));
			return -1;
		}
		*remove_path_len = Z_STRLEN_PP(option); 
		*remove_path = Z_STRVAL_PP(option);
	}

	if (zend_hash_find(HASH_OF(options), "STR"), (void **)&option) == SUCCESS) {
		if (Z_TYPE_PP(option) != IS_STRING) {
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR");
			return -1;
		}

		if (Z_STRLEN_PP(option) < 1) {
			php_error_docref(NULL TSRMLS_CC, E_NOTICE, "STR");
			return -1;
		}

		if (Z_STRLEN_PP(option) >= MAXPATHLEN) {
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR", 
						MAXPATHLEN - 1, Z_STRLEN_PP(option));
			return -1;
		}
		*add_path_len = Z_STRLEN_PP(option); 
		*add_path = Z_STRVAL_PP(option);
	}
	return 1;
}