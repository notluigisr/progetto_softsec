PHP_MINIT_FUNCTION(http_url)
{
	zend_class_entry ce = {0};

	INIT_NS_CLASS_ENTRY(ce, "STR", php_http_url_methods);
	php_http_url_class_entry = zend_register_internal_class(&ce TSRMLS_CC);

	zend_declare_property_null(php_http_url_class_entry, ZEND_STRL("STR"), ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_null(php_http_url_class_entry, ZEND_STRL("STR"), ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_null(php_http_url_class_entry, ZEND_STRL("STR"), ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_null(php_http_url_class_entry, ZEND_STRL("STR"), ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_null(php_http_url_class_entry, ZEND_STRL("STR"), ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_null(php_http_url_class_entry, ZEND_STRL("STR"), ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_null(php_http_url_class_entry, ZEND_STRL("STR"), ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_null(php_http_url_class_entry, ZEND_STRL("STR"), ZEND_ACC_PUBLIC TSRMLS_CC);

	zend_declare_class_constant_long(php_http_url_class_entry, ZEND_STRL("STR"), PHP_HTTP_URL_REPLACE TSRMLS_CC);
	zend_declare_class_constant_long(php_http_url_class_entry, ZEND_STRL("STR"), PHP_HTTP_URL_JOIN_PATH TSRMLS_CC);
	zend_declare_class_constant_long(php_http_url_class_entry, ZEND_STRL("STR"), PHP_HTTP_URL_JOIN_QUERY TSRMLS_CC);
	zend_declare_class_constant_long(php_http_url_class_entry, ZEND_STRL("STR"), PHP_HTTP_URL_STRIP_USER TSRMLS_CC);
	zend_declare_class_constant_long(php_http_url_class_entry, ZEND_STRL("STR"), PHP_HTTP_URL_STRIP_PASS TSRMLS_CC);
	zend_declare_class_constant_long(php_http_url_class_entry, ZEND_STRL("STR"), PHP_HTTP_URL_STRIP_AUTH TSRMLS_CC);
	zend_declare_class_constant_long(php_http_url_class_entry, ZEND_STRL("STR"), PHP_HTTP_URL_STRIP_PORT TSRMLS_CC);
	zend_declare_class_constant_long(php_http_url_class_entry, ZEND_STRL("STR"), PHP_HTTP_URL_STRIP_PATH TSRMLS_CC);
	zend_declare_class_constant_long(php_http_url_class_entry, ZEND_STRL("STR"), PHP_HTTP_URL_STRIP_QUERY TSRMLS_CC);
	zend_declare_class_constant_long(php_http_url_class_entry, ZEND_STRL("STR"), PHP_HTTP_URL_STRIP_FRAGMENT TSRMLS_CC);
	zend_declare_class_constant_long(php_http_url_class_entry, ZEND_STRL("STR"), PHP_HTTP_URL_STRIP_ALL TSRMLS_CC);
	zend_declare_class_constant_long(php_http_url_class_entry, ZEND_STRL("STR"), PHP_HTTP_URL_FROM_ENV TSRMLS_CC);
	zend_declare_class_constant_long(php_http_url_class_entry, ZEND_STRL("STR"), PHP_HTTP_URL_SANITIZE_PATH TSRMLS_CC);

#ifdef PHP_HTTP_HAVE_WCHAR
	zend_declare_class_constant_long(php_http_url_class_entry, ZEND_STRL("STR"), PHP_HTTP_URL_PARSE_MBLOC TSRMLS_CC);
#endif
	zend_declare_class_constant_long(php_http_url_class_entry, ZEND_STRL("STR"), PHP_HTTP_URL_PARSE_MBUTF8 TSRMLS_CC);
#if defined(PHP_HTTP_HAVE_IDN2) || defined(PHP_HTTP_HAVE_IDN) || defined(HAVE_UIDNA_IDNTOASCII)
	zend_declare_class_constant_long(php_http_url_class_entry, ZEND_STRL("STR"), PHP_HTTP_URL_PARSE_TOIDN TSRMLS_CC);
#endif
	zend_declare_class_constant_long(php_http_url_class_entry, ZEND_STRL("STR"), PHP_HTTP_URL_PARSE_TOPCT TSRMLS_CC);

	return SUCCESS;
}