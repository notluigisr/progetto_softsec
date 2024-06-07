PHP_FUNCTION(oci_lob_import)
{
	zval **tmp, *z_descriptor = getThis();
	php_oci_descriptor *descriptor;
	char *filename;
	int filename_len;

	if (getThis()) {
		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR", &filename, &filename_len) == FAILURE) {
			return;
		}
	}
	else {
		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR", &z_descriptor, oci_lob_class_entry_ptr, &filename, &filename_len) == FAILURE) {
			return;
		}	
	}

	if (strlen(filename) != filename_len) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR");
		RETURN_FALSE;  
	}

	if (zend_hash_find(Z_OBJPROP_P(z_descriptor), "STR"), (void **)&tmp) == FAILURE) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR");
		RETURN_FALSE;
	}
	
	PHP_OCI_ZVAL_TO_DESCRIPTOR(*tmp, descriptor);

	if (php_oci_lob_import(descriptor, filename TSRMLS_CC)) {
		RETURN_FALSE;
	}
	RETURN_TRUE;
}