PHP_FUNCTION(dom_document_create_text_node)
{
	zval *id;
	xmlNode *node;
	xmlDocPtr docp;
	int ret, value_len;
	dom_object *intern;
	char *value;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "STR", &id, dom_document_class_entry, &value, &value_len) == FAILURE) {
		return;
	}

	DOM_GET_OBJ(docp, id, xmlDocPtr, intern);

	node = xmlNewDocText(docp, (xmlChar *) value);
	if (!node) {
		RETURN_FALSE;
	}

	DOM_RET_OBJ(node, &ret, intern);
}