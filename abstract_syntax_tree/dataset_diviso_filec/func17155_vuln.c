PHP_METHOD(Phar, offsetGet)
{
	char *fname, *error;
	size_t fname_len;
	zval zfname;
	phar_entry_info *entry;
	zend_string *sfname;
	PHAR_ARCHIVE_OBJECT();

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "STR", &fname, &fname_len) == FAILURE) {
		return;
	}

	
	if (!(entry = phar_get_entry_info_dir(phar_obj->archive, fname, fname_len, 1, &error, 0))) {
		zend_throw_exception_ex(spl_ce_BadMethodCallException, 0, "STR");
	} else {
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

		if (entry->is_temp_dir) {
			efree(entry->filename);
			efree(entry);
		}

		sfname = strpprintf(0, "STR", phar_obj->archive->fname, fname);
		ZVAL_NEW_STR(&zfname, sfname);
		spl_instantiate_arg_ex1(phar_obj->spl.info_class, return_value, &zfname);
		zval_ptr_dtor(&zfname);
	}
}