PHP_FUNCTION(xsl_xsltprocessor_set_security_prefs)
{
	zval *id;
	xsl_object *intern;
	long securityPrefs, oldSecurityPrefs;

	DOM_GET_THIS(id);
 	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR", &securityPrefs) == FAILURE) {
		return;
	}
	intern = (xsl_object *)zend_object_store_get_object(id TSRMLS_CC);
	oldSecurityPrefs = intern->securityPrefs; 
	intern->securityPrefs = securityPrefs;
	
	intern->securityPrefsSet = 1;
	RETURN_LONG(oldSecurityPrefs);
}