int static spl_array_object_count_elements_helper(spl_array_object *intern, long *count TSRMLS_DC) 
{
	HashTable *aht = spl_array_get_hash_table(intern, 0 TSRMLS_CC);
	HashPosition pos;

	if (!aht) {
		php_error_docref(NULL TSRMLS_CC, E_NOTICE, "STR");
		*count = 0;
		return FAILURE;
	}

	if (Z_TYPE_P(intern->array) == IS_OBJECT) {
		
		pos = intern->pos;
		*count = 0;
		spl_array_rewind(intern TSRMLS_CC);
		while(intern->pos && spl_array_next(intern TSRMLS_CC) == SUCCESS) {
			(*count)++;
		}
		spl_array_set_pos(intern, pos);
		return SUCCESS;
	} else {
		*count = zend_hash_num_elements(aht);
		return SUCCESS;
	}
} 