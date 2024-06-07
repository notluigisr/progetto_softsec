PHPAPI void php_clear_stat_cache(zend_bool clear_realpath_cache, const char *filename, int filename_len TSRMLS_DC)
{
	
	if (BG(CurrentStatFile)) {
		efree(BG(CurrentStatFile));
		BG(CurrentStatFile) = NULL;
	}
	if (BG(CurrentLStatFile)) {
		efree(BG(CurrentLStatFile));
		BG(CurrentLStatFile) = NULL;
	}
	if (clear_realpath_cache) {
		if (filename != NULL) {
			realpath_cache_del(filename, filename_len TSRMLS_CC);
		} else {
			realpath_cache_clean(TSRMLS_C);
		}
	}
}