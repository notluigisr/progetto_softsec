HashTable* php_imagickkernel_get_debug_info(zval *obj, int *is_temp TSRMLS_DC) 
{
	php_imagickkernel_object *internp;
	HashTable *debug_info;
	KernelInfo *kernel_info;
#ifdef ZEND_ENGINE_3
	zval matrix;
#else
	zval *matrix;
#endif

	*is_temp = 1; 

	internp = Z_IMAGICKKERNEL_P(obj);
	kernel_info = internp->kernel_info;

	ALLOC_HASHTABLE(debug_info);
	ZEND_INIT_SYMTABLE_EX(debug_info, 1, 0);

	while (kernel_info != NULL) {
#ifdef ZEND_ENGINE_3
		array_init(&matrix);
		php_imagickkernelvalues_to_zval(&matrix, kernel_info);
		zend_hash_next_index_insert(debug_info, &matrix);
#else
		MAKE_STD_ZVAL(matrix);
		array_init(matrix);
		php_imagickkernelvalues_to_zval(matrix, kernel_info);
		zend_hash_next_index_insert(debug_info, &matrix, sizeof(zval *), NULL);
#endif
		kernel_info = kernel_info->next;
	}

	return debug_info;
}