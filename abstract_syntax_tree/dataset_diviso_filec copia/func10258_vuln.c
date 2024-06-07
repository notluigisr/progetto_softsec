PHP_FUNCTION(grapheme_stripos)
{
	unsigned char *haystack, *needle, *haystack_dup, *needle_dup;
	int haystack_len, needle_len;
	unsigned char *found;
	long loffset = 0;
	int32_t offset = 0;
	int ret_pos;
	int is_ascii;

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


	is_ascii = ( grapheme_ascii_check(haystack, haystack_len) >= 0 );

	if ( is_ascii ) {
		needle_dup = (unsigned char *)estrndup((char *)needle, needle_len);
		php_strtolower((char *)needle_dup, needle_len);
		haystack_dup = (unsigned char *)estrndup((char *)haystack, haystack_len);
		php_strtolower((char *)haystack_dup, haystack_len);

		found = (unsigned char*) php_memnstr((char *)haystack_dup + offset, (char *)needle_dup, needle_len, (char *)haystack_dup + haystack_len);

		efree(haystack_dup);
		efree(needle_dup);

		if (found) {
			RETURN_LONG(found - haystack_dup);
		}

		
		if ( grapheme_ascii_check(needle, needle_len) >= 0 ) {
			RETURN_FALSE;
		}
	}

	
	ret_pos = grapheme_strpos_utf16(haystack, haystack_len, needle, needle_len, offset, NULL, 1 , 0  TSRMLS_CC );

	if ( ret_pos >= 0 ) {
		RETURN_LONG(ret_pos);
	} else {
		RETURN_FALSE;
	}

}