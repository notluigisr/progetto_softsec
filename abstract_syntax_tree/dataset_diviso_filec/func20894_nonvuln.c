PHP_METHOD(Phar, count)
{
	
	long mode;
	PHAR_ARCHIVE_OBJECT();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR", &mode) == FAILURE) {
		RETURN_FALSE;
	}

	RETURN_LONG(zend_hash_num_elements(&phar_obj->arc.archive->manifest));
}