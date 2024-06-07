PHP_FUNCTION(rewinddir)
{
	zval *id = NULL, **tmp, *myself;
	php_stream *dirp;
	
	FETCH_DIRP();

	if (!(dirp->flags & PHP_STREAM_FLAG_IS_DIR)) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR", dirp->rsrc_id);
		RETURN_FALSE;
	}

	php_stream_rewinddir(dirp);
}