static void xml_set_handler(zval *handler, zval *data)
{
	
	if (handler) {
		zval_ptr_dtor(handler);
	}

	
	if (Z_TYPE_P(data) != IS_ARRAY && Z_TYPE_P(data) != IS_OBJECT) {
		convert_to_string_ex(data);
		if (Z_STRLEN_P(data) == 0) {
			ZVAL_UNDEF(handler);
			return;
		}
	}

	ZVAL_COPY(handler, data);
}