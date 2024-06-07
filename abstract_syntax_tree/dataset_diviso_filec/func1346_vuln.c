static zval **spl_array_get_dimension_ptr_ptr(int check_inherited, zval *object, zval *offset, int type TSRMLS_DC) 
{
	spl_array_object *intern = (spl_array_object*)zend_object_store_get_object(object TSRMLS_CC);
	zval **retval;
	long index;
	HashTable *ht = spl_array_get_hash_table(intern, 0 TSRMLS_CC);

	if (!offset) {
		return &EG(uninitialized_zval_ptr);
	}
	
	if ((type == BP_VAR_W || type == BP_VAR_RW) && (ht->nApplyCount > 0)) {
		zend_error(E_WARNING, "STR");
		return &EG(error_zval_ptr);;
	}

	switch(Z_TYPE_P(offset)) {
	case IS_NULL:
		Z_STRVAL_P(offset) = "";
		Z_STRLEN_P(offset) = 0;
	case IS_STRING:
		if (zend_symtable_find(ht, Z_STRVAL_P(offset), Z_STRLEN_P(offset)+1, (void **) &retval) == FAILURE) {
			switch (type) {
				case BP_VAR_R:
					zend_error(E_NOTICE, "STR", Z_STRVAL_P(offset));
				case BP_VAR_UNSET:
				case BP_VAR_IS:
					retval = &EG(uninitialized_zval_ptr);
					break;
				case BP_VAR_RW:
					zend_error(E_NOTICE,"STR", Z_STRVAL_P(offset));
				case BP_VAR_W: {
				    zval *value;
				    ALLOC_INIT_ZVAL(value);
				    zend_symtable_update(ht, Z_STRVAL_P(offset), Z_STRLEN_P(offset)+1, (void**)&value, sizeof(void*), (void **)&retval);
				}
			}
		}
		return retval;
	case IS_RESOURCE:
		zend_error(E_STRICT, "STR", Z_LVAL_P(offset), Z_LVAL_P(offset));
	case IS_DOUBLE:
	case IS_BOOL: 
	case IS_LONG: 
		if (offset->type == IS_DOUBLE) {
			index = (long)Z_DVAL_P(offset);
		} else {
			index = Z_LVAL_P(offset);
		}
		if (zend_hash_index_find(ht, index, (void **) &retval) == FAILURE) {
			switch (type) {
				case BP_VAR_R:
					zend_error(E_NOTICE, "STR", index);
				case BP_VAR_UNSET:
				case BP_VAR_IS:
					retval = &EG(uninitialized_zval_ptr);
					break;
				case BP_VAR_RW:
					zend_error(E_NOTICE, "STR", index);
				case BP_VAR_W: {
				    zval *value;
				    ALLOC_INIT_ZVAL(value);
					zend_hash_index_update(ht, index, (void**)&value, sizeof(void*), (void **)&retval);
			   }
			}
		}
		return retval;
	default:
		zend_error(E_WARNING, "STR");
		return (type == BP_VAR_W || type == BP_VAR_RW) ?
			&EG(error_zval_ptr) : &EG(uninitialized_zval_ptr);
	}
} 