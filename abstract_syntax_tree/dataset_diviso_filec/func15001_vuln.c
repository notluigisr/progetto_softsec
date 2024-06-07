static HashTable *spl_object_storage_get_gc(zval *obj, zval ***table, int *n TSRMLS_DC) 
{
	spl_SplObjectStorage *intern = (spl_SplObjectStorage*)zend_object_store_get_object(obj TSRMLS_CC);
	spl_SplObjectStorageElement *element;
	HashTable *props;
	HashPosition pos;
	zval *gcdata_arr = NULL,
		 **gcdata_arr_pp;

	props = std_object_handlers.get_properties(obj TSRMLS_CC);
	
	*table = NULL;
	*n = 0;

	
	if (zend_hash_find(props, "STR"), (void**) &gcdata_arr_pp) == SUCCESS) {
		gcdata_arr = *gcdata_arr_pp;
		zend_hash_clean(Z_ARRVAL_P(gcdata_arr));
	}

	if (gcdata_arr == NULL) {
		MAKE_STD_ZVAL(gcdata_arr);
		array_init(gcdata_arr);
		
		Z_ARRVAL_P(gcdata_arr)->pDestructor = NULL;

		
		zend_hash_add(props, "STR"), &gcdata_arr, sizeof(gcdata_arr), NULL);
	}

	zend_hash_internal_pointer_reset_ex(&intern->storage, &pos);
	while (zend_hash_get_current_data_ex(&intern->storage, (void **)&element, &pos) == SUCCESS) {
		add_next_index_zval(gcdata_arr, element->obj);
		add_next_index_zval(gcdata_arr, element->inf);
		zend_hash_move_forward_ex(&intern->storage, &pos);
	}

	return props;
}