PHPAPI PHP_FUNCTION(fread)
{
	zval *arg1;
	long len;
	php_stream *stream;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR", &arg1, &len) == FAILURE) {
		RETURN_FALSE;
	}

	PHP_STREAM_TO_ZVAL(stream, &arg1);

	if (len <= 0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR");
		RETURN_FALSE;
	}

	Z_STRVAL_P(return_value) = emalloc(len + 1);
	Z_STRLEN_P(return_value) = php_stream_read(stream, Z_STRVAL_P(return_value), len);

	
	Z_STRVAL_P(return_value)[Z_STRLEN_P(return_value)] = 0;
	Z_TYPE_P(return_value) = IS_STRING;
}