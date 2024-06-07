   Create an initialization vector (IV) */
PHP_FUNCTION(mcrypt_create_iv)
{
	char *iv;
	long source = RANDOM;
	long size;
	int n = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR", &size, &source) == FAILURE) {
		return;
	}

	if (size <= 0 || size >= INT_MAX) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR", INT_MAX);
		RETURN_FALSE;
	}
	
	iv = ecalloc(size + 1, 1);
	
	if (source == RANDOM || source == URANDOM) {
#if PHP_WIN32
		
		BYTE *iv_b = (BYTE *) iv;
		if (php_win32_get_random_bytes(iv_b, (size_t) size) == FAILURE){
			efree(iv);
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR");
			RETURN_FALSE;
		}
		n = size;
#else
		int    *fd = &MCG(fd[source]);
		size_t read_bytes = 0;

		if (*fd < 0) {
			*fd = open(source == RANDOM ? "STR", O_RDONLY);
			if (*fd < 0) {
				efree(iv);
				php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR");
				RETURN_FALSE;
			}
		}

		while (read_bytes < size) {
			n = read(*fd, iv + read_bytes, size - read_bytes);
			if (n < 0) {
				break;
			}
			read_bytes += n;
		}
		n = read_bytes;

		if (n < size) {
			efree(iv);
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR");
			RETURN_FALSE;
		}
#endif
	} else {
		n = size;
		while (size) {
			iv[--size] = (char) (255.0 * php_rand(TSRMLS_C) / RAND_MAX);
		}
	}
	RETURN_STRINGL(iv, n, 0);