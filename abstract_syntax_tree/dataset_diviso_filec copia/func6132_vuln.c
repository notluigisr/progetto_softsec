PHP_FUNCTION(xml_set_object)
{
	xml_parser *parser;
	zval *pind, *mythis;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR", &pind, &mythis) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(parser,xml_parser *, &pind, -1, "STR", le_xml_parser);

	
	if (parser->object) {
		zval_ptr_dtor(&parser->object);
	}

	


	ALLOC_ZVAL(parser->object);
	MAKE_COPY_ZVAL(&mythis, parser->object);

	RETVAL_TRUE;
}