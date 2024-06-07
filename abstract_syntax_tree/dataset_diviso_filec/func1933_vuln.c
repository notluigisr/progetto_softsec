PHP_FUNCTION(grapheme_strpos)
{
	unsigned char *haystack, *needle;
	int haystack_len, needle_len;
	unsigned char *found;
	long loffset = 0;
	int32_t offset = 0;
	int ret_pos;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR", (char **)&haystack, &haystack_len, (char **)&needle, &needle_len, &loffset) == FAILURE) {

		intl_error_set( NULL, U_ILLEGAL_ARGUMENT_ERROR,
			 "STR", 0 TSRMLS_CC );

		RETURN_FALSE;
	}

	if ( OUTSIDE_STRING(loffset, haystack_len) ) {

		intl_error_set( NULL, U_ILLEGAL_ARGUMENT_ERROR, "STR", 1 TSRMLS_CC );

		RETURN_FALSE;
	}

	
	offset = (int32_t) loffset;

	

	if (needle_len == 0) {

		intl_error_set( NULL, U_ILLEGAL_ARGUMENT_ERROR, "STR", 1 TSRMLS_CC );

		RETURN_FALSE;
	}


	
	found = (unsigned char *)php_memnstr((char *)haystack + offset, (char *)needle, needle_len, (char *)haystack + haystack_len);

	
	if (!found) {
		RETURN_FALSE;
	}

	
	if ( grapheme_ascii_check(haystack, haystack_len) >= 0 ) {

		RETURN_LONG(found - haystack);
	}

	
	ret_pos = grapheme_strpos_utf16(haystack, haystack_len, needle, needle_len, offset, NULL, 0 , 0  TSRMLS_CC );

	if ( ret_pos >= 0 ) {
		RETURN_LONG(ret_pos);
	} else {
		RETURN_FALSE;
	}

}