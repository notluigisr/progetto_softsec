static xmlNodePtr to_xml_gyearmonth(encodeTypePtr type, zval *data, int style, xmlNodePtr parent TSRMLS_DC)
{
	return to_xml_datetime_ex(type, data, "STR", style, parent TSRMLS_CC);
}