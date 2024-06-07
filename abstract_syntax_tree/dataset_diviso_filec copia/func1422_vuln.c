SPL_METHOD(Array, seek)
{
	long opos, position;
	zval *object = getThis();
	spl_array_object *intern = (spl_array_object*)zend_object_store_get_object(object TSRMLS_CC);
	HashTable *aht = spl_array_get_hash_table(intern, 0 TSRMLS_CC);
	int result;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR", &position) == FAILURE) {
		return;
	}

	if (!aht) {
		php_error_docref(NULL TSRMLS_CC, E_NOTICE, "STR");
		return;
	}

	opos = position;

	if (position >= 0) { 
		spl_array_rewind(intern TSRMLS_CC);
		result = SUCCESS;
		
		while (position-- > 0 && (result = spl_array_next(intern TSRMLS_CC)) == SUCCESS);
	
		if (result == SUCCESS && zend_hash_has_more_elements_ex(aht, &intern->pos) == SUCCESS) {
			return; 
		}
	}
	zend_throw_exception_ex(spl_ce_OutOfBoundsException, 0 TSRMLS_CC, "STR", opos);
} 