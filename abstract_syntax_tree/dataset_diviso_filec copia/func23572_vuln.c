static int spl_array_has_dimension_ex(int check_inherited, zval *object, zval *offset, int check_empty TSRMLS_DC) 
{
	spl_array_object *intern = (spl_array_object*)zend_object_store_get_object(object TSRMLS_CC);
	long index;
	zval *rv, **tmp;

	if (check_inherited && intern->fptr_offset_has) {
		SEPARATE_ARG_IF_REF(offset);
		zend_call_method_with_1_params(&object, Z_OBJCE_P(object), &intern->fptr_offset_has, "STR", &rv, offset);
		zval_ptr_dtor(&offset);
		if (rv && zend_is_true(rv)) {
			zval_ptr_dtor(&rv);
			return 1;
		}
		if (rv) {
			zval_ptr_dtor(&rv);
		}
		return 0;
	}
	
	switch(Z_TYPE_P(offset)) {
		case IS_STRING:
			{
				HashTable *ht = spl_array_get_hash_table(intern, 0 TSRMLS_CC);
				if (zend_symtable_find(ht, Z_STRVAL_P(offset), Z_STRLEN_P(offset)+1, (void **) &tmp) != FAILURE) {
					switch (check_empty) {
						case 0:
							return Z_TYPE_PP(tmp) != IS_NULL;
						case 2:
							return 1;
						default:
							return zend_is_true(*tmp);
					}
				}
			}
			return 0;
		case IS_DOUBLE:
		case IS_RESOURCE:
		case IS_BOOL: 
		case IS_LONG:
			{	
				HashTable *ht = spl_array_get_hash_table(intern, 0 TSRMLS_CC);
				if (offset->type == IS_DOUBLE) {
					index = (long)Z_DVAL_P(offset);
				} else {
					index = Z_LVAL_P(offset);
				}
				if (zend_hash_index_find(ht, index, (void **)&tmp) != FAILURE) {
					switch (check_empty) {
						case 0:
							return Z_TYPE_PP(tmp) != IS_NULL;
						case 2:
							return 1;
						default:
							return zend_is_true(*tmp);
					}
				}
				return 0;
			}
		default:
			zend_error(E_WARNING, "STR");
	}
	return 0;
} 