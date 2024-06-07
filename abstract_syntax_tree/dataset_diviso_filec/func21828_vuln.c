PHP_FUNCTION(pcntl_getpriority)
{
	long who = PRIO_PROCESS;
	long pid = getpid();
	int pri;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR", &pid, &who) == FAILURE) {
		RETURN_FALSE;
	}

	 
	errno = 0;

	pri = getpriority(who, pid);

	if (errno) {
		PCNTL_G(last_error) = errno;
		switch (errno) {
			case ESRCH:
				php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR", errno);
				break;
			case EINVAL:
				php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR", errno);
				break;
			default:
				php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR", errno);
				break;
		}
		RETURN_FALSE;
	}

	RETURN_LONG(pri);
}