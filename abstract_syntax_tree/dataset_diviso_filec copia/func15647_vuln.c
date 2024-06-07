PHP_FUNCTION(pcntl_setpriority)
{
	long who = PRIO_PROCESS;
	long pid = getpid();
	long pri;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR", &pri, &pid, &who) == FAILURE) {
		RETURN_FALSE;
	}

	if (setpriority(who, pid, pri)) {
		PCNTL_G(last_error) = errno;
		switch (errno) {
			case ESRCH:
				php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR", errno);
				break;
			case EINVAL:
				php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR", errno);
				break;
			case EPERM:
				php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR", errno);
				break;
			case EACCES:
				php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR", errno);
				break;
			default:
				php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR", errno);
				break;
		}
		RETURN_FALSE;
	}
	
	RETURN_TRUE;
}