PHP_FUNCTION(link)
{
	char *topath, *frompath;
	size_t topath_len, frompath_len;
	int ret;
	char source_p[MAXPATHLEN];
	char dest_p[MAXPATHLEN];
	wchar_t *dstw, *srcw;

	
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "STR", &frompath, &frompath_len, &topath, &topath_len) == FAILURE) {
		return;
	}

	if (!expand_filepath(frompath, source_p) || !expand_filepath(topath, dest_p)) {
		php_error_docref(NULL, E_WARNING, "STR");
		RETURN_FALSE;
	}

	if (php_stream_locate_url_wrapper(source_p, NULL, STREAM_LOCATE_WRAPPERS_ONLY) ||
		php_stream_locate_url_wrapper(dest_p, NULL, STREAM_LOCATE_WRAPPERS_ONLY) )
	{
		php_error_docref(NULL, E_WARNING, "STR");
		RETURN_FALSE;
	}

	if (OPENBASEDIR_CHECKPATH(source_p)) {
		RETURN_FALSE;
	}

	if (OPENBASEDIR_CHECKPATH(dest_p)) {
		RETURN_FALSE;
	}

#ifndef ZTS
# define _TO_PATH topath
# define _FROM_PATH frompath
#else
# define _TO_PATH dest_p
# define _FROM_PATH source_p
#endif
	dstw = php_win32_ioutil_any_to_w(_TO_PATH);
	if (!dstw) {
		php_error_docref(NULL, E_WARNING, "STR", GetLastError());
		RETURN_FALSE;
	}
	srcw = php_win32_ioutil_any_to_w(_FROM_PATH);
	if (!srcw) {
		free(dstw);
		php_error_docref(NULL, E_WARNING, "STR", GetLastError());
		RETURN_FALSE;
	}
#undef _TO_PATH
#undef _FROM_PATH

	ret = CreateHardLinkW(dstw, srcw, NULL);

	if (ret == 0) {
		free(dstw);
		free(srcw);
		php_error_docref(NULL, E_WARNING, "STR", strerror(errno));
		RETURN_FALSE;
	}

	free(dstw);
	free(srcw);

	RETURN_TRUE;
}