static XMLRPC_VALUE PHP_to_XMLRPC_worker (const char* key, zval* in_val, int depth)
{
	XMLRPC_VALUE xReturn = NULL;

	if (in_val) {
		zval val;
		XMLRPC_VALUE_TYPE type;

		ZVAL_UNDEF(&val);
		type = get_zval_xmlrpc_type(in_val, &val);

		if (!Z_ISUNDEF(val)) {
			switch (type) {
				case xmlrpc_base64:
					if (Z_TYPE(val) == IS_NULL) {
						xReturn = XMLRPC_CreateValueEmpty();
						XMLRPC_SetValueID(xReturn, key, 0);
					} else {
						xReturn = XMLRPC_CreateValueBase64(key, Z_STRVAL(val), Z_STRLEN(val));
					}
					break;
				case xmlrpc_datetime:
					convert_to_string(&val);
					xReturn = XMLRPC_CreateValueDateTime_ISO8601(key, Z_STRVAL(val));
					break;
				case xmlrpc_boolean:
					convert_to_boolean(&val);
					xReturn = XMLRPC_CreateValueBoolean(key, Z_TYPE(val) == IS_TRUE);
					break;
				case xmlrpc_int:
					convert_to_long(&val);
					xReturn = XMLRPC_CreateValueInt(key, Z_LVAL(val));
					break;
				case xmlrpc_double:
					convert_to_double(&val);
					xReturn = XMLRPC_CreateValueDouble(key, Z_DVAL(val));
					break;
				case xmlrpc_string:
					convert_to_string(&val);
					xReturn = XMLRPC_CreateValueString(key, Z_STRVAL(val), Z_STRLEN(val));
					break;
				case xmlrpc_vector:
					{
						zend_ulong num_index;
						zval* pIter;
						zend_string* my_key;
						HashTable *ht = NULL;
						zval val_arr;
						XMLRPC_VECTOR_TYPE vtype;

						ht = HASH_OF(&val);
						if (ht && ht->u.v.nApplyCount > 1) {
							php_error_docref(NULL, E_ERROR, "STR");
							return NULL;
						}

						ZVAL_COPY(&val_arr, &val);
						convert_to_array(&val_arr);

						vtype = determine_vector_type(Z_ARRVAL(val_arr));
						xReturn = XMLRPC_CreateVector(key, vtype);

						ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL(val_arr), num_index, my_key, pIter) {
							ht = HASH_OF(pIter);
							if (ht) {
								ht->u.v.nApplyCount++;
							}
							if (my_key == NULL) {
								char *num_str = NULL;

								if (vtype != xmlrpc_vector_array) {
									spprintf(&num_str, 0, "STR", num_index);
								}

								XMLRPC_AddValueToVector(xReturn, PHP_to_XMLRPC_worker(num_str, pIter, depth++));
								if (num_str) {
									efree(num_str);
								}
							} else {
								XMLRPC_AddValueToVector(xReturn, PHP_to_XMLRPC_worker(ZSTR_VAL(my_key), pIter, depth++));
							}
							if (ht) {
								ht->u.v.nApplyCount--;
							}
						} ZEND_HASH_FOREACH_END();
						zval_ptr_dtor(&val_arr);
					}
					break;
				default:
					break;
			}
		}
	}
	return xReturn;
}