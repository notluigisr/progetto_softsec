static inline int object_common2(UNSERIALIZE_PARAMETER, long elements)
{
	zval *retval_ptr = NULL;
	zval fname;

	if (!process_nested_data(UNSERIALIZE_PASSTHRU, Z_OBJPROP_PP(rval), elements)) {
		return 0;
	}

	if (Z_OBJCE_PP(rval) != PHP_IC_ENTRY &&
		zend_hash_exists(&Z_OBJCE_PP(rval)->function_table, "STR"))) {
		INIT_PZVAL(&fname);
		ZVAL_STRINGL(&fname, "STR") - 1, 0);
		call_user_function_ex(CG(function_table), rval, &fname, &retval_ptr, 0, 0, 1, NULL TSRMLS_CC);
	}

	if (retval_ptr)
		zval_ptr_dtor(&retval_ptr);

	return finish_nested_data(UNSERIALIZE_PASSTHRU);

}