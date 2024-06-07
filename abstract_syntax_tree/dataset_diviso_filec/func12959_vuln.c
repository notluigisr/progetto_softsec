void _xml_endElementHandler(void *userData, const XML_Char *name)
{
	xml_parser *parser = (xml_parser *)userData;
	char *tag_name;

	if (parser) {
		zval *retval, *args[2];

		tag_name = _xml_decode_tag(parser, name);

		if (parser->endElementHandler) {
			args[0] = _xml_resource_zval(parser->index);
			args[1] = _xml_string_zval(((char *) tag_name) + parser->toffset);

			if ((retval = xml_call_handler(parser, parser->endElementHandler, parser->endElementPtr, 2, args))) {
				zval_ptr_dtor(&retval);
			}
		} 

		if (parser->data) {
			zval *tag;

			if (parser->lastwasopen) {
				add_assoc_string(*(parser->ctag),"STR",1);
			} else {
				MAKE_STD_ZVAL(tag);

				array_init(tag);
				  
				_xml_add_to_info(parser,((char *) tag_name) + parser->toffset);

				add_assoc_string(tag,"STR",((char *) tag_name) + parser->toffset,1); 
				add_assoc_string(tag,"STR",1);
				add_assoc_long(tag,"STR",parser->level);
				  
				zend_hash_next_index_insert(Z_ARRVAL_P(parser->data),&tag,sizeof(zval*),NULL);
			}

			parser->lastwasopen = 0;
		}

		efree(tag_name);

		if (parser->ltags) {
			efree(parser->ltags[parser->level-1]);
		}

		parser->level--;
	}
}