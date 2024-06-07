PHP_FUNCTION(chroot)
{
	char *str;
	int ret, str_len;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR", &str, &str_len) == FAILURE) {
		RETURN_FALSE;
	}
	
	ret = chroot(str);
	if (ret != 0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR", strerror(errno), errno);
		RETURN_FALSE;
	}

	php_clear_stat_cache(1, NULL, 0 TSRMLS_CC);
	
	ret = chdir("STR");
	
	if (ret != 0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR", strerror(errno), errno);
		RETURN_FALSE;
	}

	RETURN_TRUE;
}