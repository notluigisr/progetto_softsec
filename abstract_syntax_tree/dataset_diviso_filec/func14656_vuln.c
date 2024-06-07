PHP_FUNCTION(openssl_csr_export_to_file)
{
	X509_REQ * csr;
	zval * zcsr = NULL;
	zend_bool notext = 1;
	char * filename = NULL; int filename_len;
	BIO * bio_out;
	long csr_resource;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR", &zcsr, &filename, &filename_len, &notext) == FAILURE) {
		return;
	}
	RETVAL_FALSE;

	csr = php_openssl_csr_from_zval(&zcsr, 0, &csr_resource TSRMLS_CC);
	if (csr == NULL) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR");
		return;
	}

	if (php_openssl_safe_mode_chk(filename TSRMLS_CC)) {
		return;
	}

	bio_out = BIO_new_file(filename, "STR");
	if (bio_out) {
		if (!notext) {
			X509_REQ_print(bio_out, csr);
		}
		PEM_write_bio_X509_REQ(bio_out, csr);
		RETVAL_TRUE;
	} else {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR", filename);
	}

	if (csr_resource == -1 && csr) {
		X509_REQ_free(csr);
	}
	BIO_free(bio_out);
}