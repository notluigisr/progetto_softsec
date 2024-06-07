PHP_FUNCTION(posix_mknod)
{
	char *path;
	int path_len;
	long mode;
	long major = 0, minor = 0;
	int result;
	dev_t php_dev;

	php_dev = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR", &path, &path_len,
			&mode, &major, &minor) == FAILURE) {
		RETURN_FALSE;
	}

	if (php_check_open_basedir_ex(path, 0 TSRMLS_CC) ||
			(PG(safe_mode) && (!php_checkuid(path, NULL, CHECKUID_ALLOW_ONLY_DIR)))) {
		RETURN_FALSE;
	}

	if ((mode & S_IFCHR) || (mode & S_IFBLK)) {
		if (ZEND_NUM_ARGS() == 2) {
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR");
			RETURN_FALSE;
		}
		if (major == 0) {
			php_error_docref(NULL TSRMLS_CC, E_WARNING,
				"STR");
			RETURN_FALSE;
		} else {
#if defined(HAVE_MAKEDEV) || defined(makedev)
			php_dev = makedev(major, minor);
#else
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR");
#endif
		}
	}

	result = mknod(path, mode, php_dev);
	if (result < 0) {
		POSIX_G(last_error) = errno;
		RETURN_FALSE;
	}

	RETURN_TRUE;
}