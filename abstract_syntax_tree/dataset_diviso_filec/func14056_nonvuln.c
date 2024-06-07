   Returns associative array with detailed info about given date
*/
PHP_FUNCTION(date_parse)
{
	char                           *date;
	int                             date_len;
	struct timelib_error_container *error;
	timelib_time                   *parsed_time;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR", &date, &date_len) == FAILURE) {
		RETURN_FALSE;
	}

	parsed_time = timelib_strtotime(date, date_len, &error, DATE_TIMEZONEDB, php_date_parse_tzfile_wrapper);