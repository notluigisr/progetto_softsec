PS_READ_FUNC(files)
{
	long n;
	struct stat sbuf;
	PS_FILES_DATA;

	
	if (PS(use_strict_mode) &&
		ps_files_key_exists(data, key TSRMLS_CC) == FAILURE) {
		
		if (key) {
			efree(PS(id));
			PS(id) = NULL;
		}
		PS(id) = PS(mod)->s_create_sid((void **)&data, NULL TSRMLS_CC);
		if (!PS(id)) {
			return FAILURE;
		}
		if (PS(use_cookies)) {
			PS(send_cookie) = 1;
		}
		php_session_reset_id(TSRMLS_C);
		PS(session_status) = php_session_active;
	}

	ps_files_open(data, PS(id) TSRMLS_CC);
	if (data->fd < 0) {
		return FAILURE;
	}

	if (fstat(data->fd, &sbuf)) {
		return FAILURE;
	}

	data->st_size = *vallen = sbuf.st_size;

	if (sbuf.st_size == 0) {
		*val = STR_EMPTY_ALLOC();
		return SUCCESS;
	}

	*val = emalloc(sbuf.st_size);

#if defined(HAVE_PREAD)
	n = pread(data->fd, *val, sbuf.st_size, 0);
#else
	lseek(data->fd, 0, SEEK_SET);
	n = read(data->fd, *val, sbuf.st_size);
#endif

	if (n != sbuf.st_size) {
		if (n == -1) {
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR", strerror(errno), errno);
		} else {
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR");
		}
		efree(*val);
		return FAILURE;
	}

	return SUCCESS;
}