PHP_FUNCTION(popen)
{
	char *command, *mode;
	int command_len, mode_len;
	FILE *fp;
	php_stream *stream;
	char *posix_mode, *b, *buf = 0, *tmp;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR", &command, &command_len, &mode, &mode_len) == FAILURE) {
		return;
	}

	posix_mode = estrndup(mode, mode_len);
#ifndef PHP_WIN32
	{
		char *z = memchr(posix_mode, 'b', mode_len);
		if (z) {
			memmove(z, z + 1, mode_len - (z - posix_mode));
		}
	}
#endif
	if (PG(safe_mode)){
		b = strchr(command, ' ');
		if (!b) {
			b = strrchr(command, '/');
		} else {
			char *c;

			c = command;
			while((*b != '/') && (b != c)) {
				b--;
			}
			if (b == c) {
				b = NULL;
			}
		}

		if (b) {
			spprintf(&buf, 0, "STR", PG(safe_mode_exec_dir), b);
		} else {
			spprintf(&buf, 0, "STR", PG(safe_mode_exec_dir), command);
		}

		tmp = php_escape_shell_cmd(buf);
		fp = VCWD_POPEN(tmp, posix_mode);
		efree(tmp);

		if (!fp) {
			php_error_docref2(NULL TSRMLS_CC, buf, posix_mode, E_WARNING, "STR", strerror(errno));
			efree(posix_mode);
			efree(buf);
			RETURN_FALSE;
		}

		efree(buf);

	} else {
		fp = VCWD_POPEN(command, posix_mode);
		if (!fp) {
			php_error_docref2(NULL TSRMLS_CC, command, posix_mode, E_WARNING, "STR", strerror(errno));
			efree(posix_mode);
			RETURN_FALSE;
		}
	}
	stream = php_stream_fopen_from_pipe(fp, mode);

	if (stream == NULL)	{
		php_error_docref2(NULL TSRMLS_CC, command, mode, E_WARNING, "STR", strerror(errno));
		RETVAL_FALSE;
	} else {
		php_stream_to_zval(stream, return_value);
	}

	efree(posix_mode);
}