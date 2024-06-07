PHP_FUNCTION(oci_lob_erase)
{
	zval **tmp, *z_descriptor = getThis();
	php_oci_descriptor *descriptor;
	ub4 bytes_erased;
	long offset = -1, length = -1;
	
	if (getThis()) {
		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR", &offset, &length) == FAILURE) {
			return;
		}
	
		if (ZEND_NUM_ARGS() > 0 && offset < 0) {
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR");
			RETURN_FALSE;
		}
		
		if (ZEND_NUM_ARGS() > 1 && length < 0) {
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR");
			RETURN_FALSE;
		}
	}
	else {
		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR", &z_descriptor, oci_lob_class_entry_ptr, &offset, &length) == FAILURE) {
			return;
		}
			
		if (ZEND_NUM_ARGS() > 1 && offset < 0) {
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR");
			RETURN_FALSE;
		}
		
		if (ZEND_NUM_ARGS() > 2 && length < 0) {
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR");
			RETURN_FALSE;
		}
	}
	
	if (zend_hash_find(Z_OBJPROP_P(z_descriptor), "STR"), (void **)&tmp) == FAILURE) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR");
		RETURN_FALSE;
	}

	PHP_OCI_ZVAL_TO_DESCRIPTOR(*tmp, descriptor);
	
	if (php_oci_lob_erase(descriptor, offset, length, &bytes_erased TSRMLS_CC)) {
		RETURN_FALSE;
	}
	RETURN_LONG(bytes_erased);
}