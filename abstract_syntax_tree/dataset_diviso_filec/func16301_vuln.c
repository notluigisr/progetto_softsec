static void php_bz2_error(INTERNAL_FUNCTION_PARAMETERS, int opt)
{ 
	zval         *bzp;     
	php_stream   *stream;
	const char   *errstr;  
	int           errnum;  
	struct php_bz2_stream_data_t *self;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR", &bzp) == FAILURE) {
		return;
	}

	php_stream_from_zval(stream, &bzp);

	if (!php_stream_is(stream, PHP_STREAM_IS_BZIP2)) {
		RETURN_FALSE;
	}

	self = (struct php_bz2_stream_data_t *) stream->abstract;
	
	
	errstr = BZ2_bzerror(self->bz_file, &errnum);
	
	
	switch (opt) {
		case PHP_BZ_ERRNO:
			RETURN_LONG(errnum);
			break;
		case PHP_BZ_ERRSTR:
			RETURN_STRING((char*)errstr, 1);
			break;
		case PHP_BZ_ERRBOTH:
			array_init(return_value);
		
			add_assoc_long  (return_value, "STR",  errnum);
			add_assoc_string(return_value, "STR", (char*)errstr, 1);
			break;
	}
}