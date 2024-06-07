	return FAILURE;
}

static void php_tidy_quick_repair(INTERNAL_FUNCTION_PARAMETERS, zend_bool is_file)
{
	char *data=NULL, *arg1, *enc = NULL;
	int arg1_len, enc_len = 0, data_len = 0;
	zend_bool use_include_path = 0;
	TidyDoc doc;
	TidyBuffer *errbuf;
	zval **config = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR", &arg1, &arg1_len, &config, &enc, &enc_len, &use_include_path) == FAILURE) {
		RETURN_FALSE;
	}
	
	if (is_file) {
		if (!(data = php_tidy_file_to_mem(arg1, use_include_path, &data_len TSRMLS_CC))) {
			RETURN_FALSE;
		}
	} else {
		data = arg1;
		data_len = arg1_len;
	}

	doc = tidyCreate();
	errbuf = emalloc(sizeof(TidyBuffer));
	tidyBufInit(errbuf);
	
	if (tidySetErrorBuffer(doc, errbuf) != 0) {
		tidyBufFree(errbuf);
		efree(errbuf);
		tidyRelease(doc);
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "STR");
	}
	
	tidyOptSetBool(doc, TidyForceOutput, yes);
	tidyOptSetBool(doc, TidyMark, no);
	
	TIDY_SET_DEFAULT_CONFIG(doc);
	
	if (config) {
		TIDY_APPLY_CONFIG_ZVAL(doc, config);
	}

	if(enc_len) {
		if (tidySetCharEncoding(doc, enc) < 0) {
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR", enc);
			RETVAL_FALSE;
		}
	}
	
	if (data) {
		TidyBuffer buf;

		tidyBufInit(&buf);
		tidyBufAppend(&buf, data, data_len);

		if (tidyParseBuffer(doc, &buf) < 0) {
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR", errbuf->bp);
			RETVAL_FALSE;
		} else {
			if (tidyCleanAndRepair(doc) >= 0) {
				TidyBuffer output;
				tidyBufInit(&output);

				tidySaveBuffer (doc, &output);
				RETVAL_STRINGL((char*)output.bp, output.size ? output.size-1 : 0, 1);
				tidyBufFree(&output);
			} else {
				RETVAL_FALSE;
			}
		}
		
		tidyBufFree(&buf);
	}

	if (is_file) {
		efree(data);
	}
	
	tidyBufFree(errbuf);