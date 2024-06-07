SPL_METHOD(Array, serialize)
{
	zval *object = getThis();
	spl_array_object *intern = (spl_array_object*)zend_object_store_get_object(object TSRMLS_CC);
	HashTable *aht = spl_array_get_hash_table(intern, 0 TSRMLS_CC);
	zval members, *pmembers;
	php_serialize_data_t var_hash;
	smart_str buf = {0};
	zval *flags;
	
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	if (!aht) {
		php_error_docref(NULL TSRMLS_CC, E_NOTICE, "STR");
		return;
	}

	PHP_VAR_SERIALIZE_INIT(var_hash);

	MAKE_STD_ZVAL(flags);
	ZVAL_LONG(flags, (intern->ar_flags & SPL_ARRAY_CLONE_MASK));

	
	smart_str_appendl(&buf, "STR", 2);
	php_var_serialize(&buf, &flags, &var_hash TSRMLS_CC);
	zval_ptr_dtor(&flags);

	if (!(intern->ar_flags & SPL_ARRAY_IS_SELF)) {
		php_var_serialize(&buf, &intern->array, &var_hash TSRMLS_CC);
		smart_str_appendc(&buf, ';');
	}

	
	smart_str_appendl(&buf, "STR", 2);
	INIT_PZVAL(&members);
	if (!intern->std.properties) {
		rebuild_object_properties(&intern->std);
	}
	Z_ARRVAL(members) = intern->std.properties;
	Z_TYPE(members) = IS_ARRAY;
	pmembers = &members;
	php_var_serialize(&buf, &pmembers, &var_hash TSRMLS_CC); 

	
	PHP_VAR_SERIALIZE_DESTROY(var_hash);

	if (buf.c) {
		RETURN_STRINGL(buf.c, buf.len, 0);
	}

	RETURN_NULL();
} 