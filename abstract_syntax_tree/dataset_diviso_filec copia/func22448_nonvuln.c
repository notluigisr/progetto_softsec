PHP_FUNCTION(fnmatch)
{
	char *pattern, *filename;
	int pattern_len, filename_len;
	long flags = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR", &pattern, &pattern_len, &filename, &filename_len, &flags) == FAILURE) {
		return;
	}

	if (filename_len >= MAXPATHLEN) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR", MAXPATHLEN);
		RETURN_FALSE;
	}
	if (pattern_len >= MAXPATHLEN) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR", MAXPATHLEN);
		RETURN_FALSE;
	}

	RETURN_BOOL( ! fnmatch( pattern, filename, flags ));
}