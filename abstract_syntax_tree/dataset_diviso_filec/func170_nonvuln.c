void sqlite_iterator_dtor(zend_object_iterator *iter TSRMLS_DC)
{
	zval *object = (zval*)((sqlite_object_iterator*)iter)->it.data;

	if (((sqlite_object_iterator*)iter)->value) {
		zval_ptr_dtor(&((sqlite_object_iterator*)iter)->value);
		((sqlite_object_iterator*)iter)->value = NULL;
	}
	zval_ptr_dtor(&object);
	efree(iter);
}