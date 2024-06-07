static void ps_files_open(ps_files *data, const char *key TSRMLS_DC)
{
	char buf[MAXPATHLEN];

	if (data->fd < 0 || !data->lastkey || strcmp(key, data->lastkey)) {
		if (data->lastkey) {
			efree(data->lastkey);
			data->lastkey = NULL;
		}

		ps_files_close(data);

		if (!ps_files_valid_key(key)) {
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR");
			PS(invalid_session_id) = 1;
			return;
		}
		if (!ps_files_path_create(buf, sizeof(buf), data, key)) {
			return;
		}

		data->lastkey = estrdup(key);

		data->fd = VCWD_OPEN_MODE(buf, O_CREAT | O_RDWR | O_BINARY, data->filemode);

		if (data->fd != -1) {
#ifndef PHP_WIN32
			
			if (PG(open_basedir)) {
				struct stat sbuf;

				if (fstat(data->fd, &sbuf)) {
					close(data->fd);
					return;
				}
				if (S_ISLNK(sbuf.st_mode) && php_check_open_basedir(buf TSRMLS_CC)) {
					close(data->fd);
					return;
				}
			}
#endif
			flock(data->fd, LOCK_EX);

#ifdef F_SETFD
# ifndef FD_CLOEXEC
#  define FD_CLOEXEC 1
# endif
			if (fcntl(data->fd, F_SETFD, FD_CLOEXEC)) {
				php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR", data->fd, strerror(errno), errno);
			}
#endif
		} else {
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR", buf, strerror(errno), errno);
		}
	}
}