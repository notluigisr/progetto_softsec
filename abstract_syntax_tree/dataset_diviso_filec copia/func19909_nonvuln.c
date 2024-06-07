static zend_string *php_session_encode(void) 
{
	IF_SESSION_VARS() {
		if (!PS(serializer)) {
			php_error_docref(NULL, E_WARNING, "STR");
			return NULL;
		}
		return PS(serializer)->encode();
	} else {
		php_error_docref(NULL, E_WARNING, "STR");
	}
	return NULL;
}