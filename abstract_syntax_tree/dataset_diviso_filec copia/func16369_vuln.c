PHP_FUNCTION(pcntl_alarm)
{
	long seconds;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR", &seconds) == FAILURE)
		return;
	
	RETURN_LONG ((long) alarm(seconds));
}