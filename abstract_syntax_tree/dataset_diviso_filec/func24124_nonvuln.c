PHP_FUNCTION(sqlite_udf_decode_binary)
{
	char *data = NULL;
	int datalen;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR", &data, &datalen)) {
		return;
	}

	if (data == NULL) {
		RETURN_NULL();
	}
	if (datalen && data[0] == '\x01') {
		
		int enclen;
		char *ret;

		ret = emalloc(datalen);
		enclen = php_sqlite_decode_binary(data+1, ret);
		ret[enclen] = '\0';
		RETVAL_STRINGL(ret, enclen, 0);
	} else {
		RETVAL_STRINGL(data, datalen, 1);
	}
}