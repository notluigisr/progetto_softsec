PHP_FUNCTION(stream_set_chunk_size)
{
	int			ret;
	long		csize;
	zval		*zstream;
	php_stream	*stream;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR", &zstream, &csize) == FAILURE) {
		RETURN_FALSE;
	}

	if (csize <= 0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR", csize);
		RETURN_FALSE;
	}
	
	if (csize > INT_MAX) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR", INT_MAX);
		RETURN_FALSE;
	}
	
	php_stream_from_zval(stream, &zstream);

	ret = php_stream_set_option(stream, PHP_STREAM_OPTION_SET_CHUNK_SIZE, (int)csize, NULL);
	
	RETURN_LONG(ret > 0 ? (long)ret : (long)EOF);
}