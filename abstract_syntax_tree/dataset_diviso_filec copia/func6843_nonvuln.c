PHP_MSHUTDOWN_FUNCTION(soap)
{
	zend_error_cb = old_error_handler;
	zend_hash_destroy(&SOAP_GLOBAL(defEnc));
	zend_hash_destroy(&SOAP_GLOBAL(defEncIndex));
	zend_hash_destroy(&SOAP_GLOBAL(defEncNs));
	if (SOAP_GLOBAL(mem_cache)) {
		zend_hash_destroy(SOAP_GLOBAL(mem_cache));
		free(SOAP_GLOBAL(mem_cache));
	}
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}