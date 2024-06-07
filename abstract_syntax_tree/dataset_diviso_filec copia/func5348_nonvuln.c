static void php_hash_do_hash(INTERNAL_FUNCTION_PARAMETERS, int isfilename, zend_bool raw_output_default) 
{
	char *algo, *data, *digest;
	int algo_len, data_len;
	zend_bool raw_output = raw_output_default;
	const php_hash_ops *ops;
	void *context;
	php_stream *stream = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR", &algo, &algo_len, &data, &data_len, &raw_output) == FAILURE) {
		return;
	}

	ops = php_hash_fetch_ops(algo, algo_len);
	if (!ops) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR", algo);
		RETURN_FALSE;
	}
	if (isfilename) {
		if (CHECK_NULL_PATH(data, data_len)) {
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR");
			RETURN_FALSE;
		}
		stream = php_stream_open_wrapper_ex(data, "STR", REPORT_ERRORS, NULL, DEFAULT_CONTEXT);
		if (!stream) {
			
			RETURN_FALSE;
		}
	}

	context = emalloc(ops->context_size);
	ops->hash_init(context);

	if (isfilename) {
		char buf[1024];
		int n;

		while ((n = php_stream_read(stream, buf, sizeof(buf))) > 0) {
			ops->hash_update(context, (unsigned char *) buf, n);
		}
		php_stream_close(stream);
	} else {
		ops->hash_update(context, (unsigned char *) data, data_len);
	}

	digest = emalloc(ops->digest_size + 1);
	ops->hash_final((unsigned char *) digest, context);
	efree(context);

	if (raw_output) {
		digest[ops->digest_size] = 0;
		RETURN_STRINGL(digest, ops->digest_size, 0);
	} else {
		char *hex_digest = safe_emalloc(ops->digest_size, 2, 1);

		php_hash_bin2hex(hex_digest, (unsigned char *) digest, ops->digest_size);
		hex_digest[2 * ops->digest_size] = 0;
		efree(digest);
		RETURN_STRINGL(hex_digest, 2 * ops->digest_size, 0);
	}
}