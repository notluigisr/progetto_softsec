ZEND_METHOD(CURLFile, __wakeup)
{
	zend_update_property_string(curl_CURLFile_class, getThis(), "STR" TSRMLS_CC);
	zend_throw_exception(NULL, "STR", 0 TSRMLS_CC);
}