PHP_METHOD(Phar, offsetSet)
{
	char *fname, *cont_str = NULL;
	size_t fname_len, cont_len;
	zval *zresource;
	PHAR_ARCHIVE_OBJECT();

	if (PHAR_G(readonly) && !phar_obj->archive->is_data) {
		zend_throw_exception_ex(spl_ce_BadMethodCallException, 0, "STR");
		return;
	}

	if (zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS(), "STR", &fname, &fname_len, &zresource) == FAILURE
	&& zend_parse_parameters(ZEND_NUM_ARGS(), "STR", &fname, &fname_len, &cont_str, &cont_len) == FAILURE) {
		return;
	}

	if (fname_len == sizeof("STR")-1)) {
		zend_throw_exception_ex(spl_ce_BadMethodCallException, 0, "STR", phar_obj->archive->fname);
		return;
	}

	if (fname_len == sizeof("STR")-1)) {
		zend_throw_exception_ex(spl_ce_BadMethodCallException, 0, "STR", phar_obj->archive->fname);
		return;
	}

	if (fname_len >= sizeof("STR")-1)) {
		zend_throw_exception_ex(spl_ce_BadMethodCallException, 0, "STR", phar_obj->archive->fname);
		return;
	}

	phar_add_file(&(phar_obj->archive), fname, fname_len, cont_str, cont_len, zresource);
}