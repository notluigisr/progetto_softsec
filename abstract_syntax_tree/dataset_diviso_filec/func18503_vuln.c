 */
static void php_wddx_serialize_object(wddx_packet *packet, zval *obj)
{

	zval **ent, *fname, **varname;
	zval *retval = NULL;
	const char *key;
	ulong idx;
	char tmp_buf[WDDX_BUF_LEN];
	HashTable *objhash, *sleephash;
	TSRMLS_FETCH();

	MAKE_STD_ZVAL(fname);
	ZVAL_STRING(fname, "STR", 1);

	
	if (call_user_function_ex(CG(function_table), &obj, fname, &retval, 0, 0, 1, NULL TSRMLS_CC) == SUCCESS) {
		if (retval && (sleephash = HASH_OF(retval))) {
			PHP_CLASS_ATTRIBUTES;

			PHP_SET_CLASS_ATTRIBUTES(obj);

			php_wddx_add_chunk_static(packet, WDDX_STRUCT_S);
			snprintf(tmp_buf, WDDX_BUF_LEN, WDDX_VAR_S, PHP_CLASS_NAME_VAR);
			php_wddx_add_chunk(packet, tmp_buf);
			php_wddx_add_chunk_static(packet, WDDX_STRING_S);
			php_wddx_add_chunk_ex(packet, class_name, name_len);
			php_wddx_add_chunk_static(packet, WDDX_STRING_E);
			php_wddx_add_chunk_static(packet, WDDX_VAR_E);

			PHP_CLEANUP_CLASS_ATTRIBUTES();

			objhash = HASH_OF(obj);

			for (zend_hash_internal_pointer_reset(sleephash);
				 zend_hash_get_current_data(sleephash, (void **)&varname) == SUCCESS;
				 zend_hash_move_forward(sleephash)) {
				if (Z_TYPE_PP(varname) != IS_STRING) {
					php_error_docref(NULL TSRMLS_CC, E_NOTICE, "STR");
					continue;
				}

				if (zend_hash_find(objhash, Z_STRVAL_PP(varname), Z_STRLEN_PP(varname)+1, (void **)&ent) == SUCCESS) {
					php_wddx_serialize_var(packet, *ent, Z_STRVAL_PP(varname), Z_STRLEN_PP(varname) TSRMLS_CC);
				}
			}

			php_wddx_add_chunk_static(packet, WDDX_STRUCT_E);
		}
	} else {
		uint key_len;

		PHP_CLASS_ATTRIBUTES;

		PHP_SET_CLASS_ATTRIBUTES(obj);

		php_wddx_add_chunk_static(packet, WDDX_STRUCT_S);
		snprintf(tmp_buf, WDDX_BUF_LEN, WDDX_VAR_S, PHP_CLASS_NAME_VAR);
		php_wddx_add_chunk(packet, tmp_buf);
		php_wddx_add_chunk_static(packet, WDDX_STRING_S);
		php_wddx_add_chunk_ex(packet, class_name, name_len);
		php_wddx_add_chunk_static(packet, WDDX_STRING_E);
		php_wddx_add_chunk_static(packet, WDDX_VAR_E);

		PHP_CLEANUP_CLASS_ATTRIBUTES();

		objhash = HASH_OF(obj);
		for (zend_hash_internal_pointer_reset(objhash);
			 zend_hash_get_current_data(objhash, (void**)&ent) == SUCCESS;
			 zend_hash_move_forward(objhash)) {
			if (*ent == obj) {
				continue;
			}

			if (zend_hash_get_current_key_ex(objhash, &key, &key_len, &idx, 0, NULL) == HASH_KEY_IS_STRING) {
				const char *class_name, *prop_name;

				zend_unmangle_property_name(key, key_len-1, &class_name, &prop_name);
				php_wddx_serialize_var(packet, *ent, prop_name, strlen(prop_name)+1 TSRMLS_CC);
			} else {
				key_len = slprintf(tmp_buf, sizeof(tmp_buf), "STR", idx);
				php_wddx_serialize_var(packet, *ent, tmp_buf, key_len TSRMLS_CC);
			}
		}
		php_wddx_add_chunk_static(packet, WDDX_STRUCT_E);
	}

	zval_dtor(fname);
	FREE_ZVAL(fname);

	if (retval) {
		zval_ptr_dtor(&retval);
	}