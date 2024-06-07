void php_filter_validate_url(PHP_INPUT_FILTER_PARAM_DECL) 
{
	php_url *url;
	size_t old_len = Z_STRLEN_P(value);

	if (flags & (FILTER_FLAG_SCHEME_REQUIRED | FILTER_FLAG_HOST_REQUIRED)) {
		php_error_docref(NULL, E_DEPRECATED,
			"STR");
	}

	php_filter_url(value, flags, option_array, charset);

	if (Z_TYPE_P(value) != IS_STRING || old_len != Z_STRLEN_P(value)) {
		RETURN_VALIDATION_FAILED
	}

	
	url = php_url_parse_ex(Z_STRVAL_P(value), Z_STRLEN_P(value));

	if (url == NULL) {
		RETURN_VALIDATION_FAILED
	}

	if (url->scheme != NULL &&
		(zend_string_equals_literal_ci(url->scheme, "STR"))) {
		char *e, *s, *t;
		size_t l;

		if (url->host == NULL) {
			goto bad_url;
		}

		s = ZSTR_VAL(url->host);
		l = ZSTR_LEN(url->host);
		e = s + l;
		t = e - 1;

		
		if (*s == '[' && *t == ']' && _php_filter_validate_ipv6((s + 1), l - 2)) {
			php_url_free(url);
			return;
		}

		
		if (!_php_filter_validate_domain(ZSTR_VAL(url->host), l, FILTER_FLAG_HOSTNAME)) {
			php_url_free(url);
			RETURN_VALIDATION_FAILED
		}
	}

	if (
		url->scheme == NULL ||
		
		(url->host == NULL && (strcmp(ZSTR_VAL(url->scheme), "STR"))) ||
		((flags & FILTER_FLAG_PATH_REQUIRED) && url->path == NULL) || ((flags & FILTER_FLAG_QUERY_REQUIRED) && url->query == NULL)
	) {
bad_url:
		php_url_free(url);
		RETURN_VALIDATION_FAILED
	}

	if (url->user != NULL && !is_userinfo_valid(url->user)) {
		php_url_free(url);
		RETURN_VALIDATION_FAILED

	}

	php_url_free(url);
}