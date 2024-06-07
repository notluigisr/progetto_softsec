PHP_FUNCTION(locale_accept_from_http)
{
	UEnumeration *available;
	char *http_accept = NULL;
	int http_accept_len;
	UErrorCode status = 0;
	int len;
	char resultLocale[INTL_MAX_LOCALE_LEN+1];
	UAcceptResult outResult;

	if(zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "STR", &http_accept, &http_accept_len) == FAILURE)
	{
		intl_error_set( NULL, U_ILLEGAL_ARGUMENT_ERROR,
		"STR", 0 TSRMLS_CC );
		RETURN_FALSE;
	}

	available = ures_openAvailableLocales(NULL, &status);
	INTL_CHECK_STATUS(status, "STR");
	len = uloc_acceptLanguageFromHTTP(resultLocale, INTL_MAX_LOCALE_LEN,
						&outResult, http_accept, available, &status);
	uenum_close(available);
	INTL_CHECK_STATUS(status, "STR");
	if (len < 0 || outResult == ULOC_ACCEPT_FAILED) {
		RETURN_FALSE;
	}
	RETURN_STRINGL(resultLocale, len, 1);
}