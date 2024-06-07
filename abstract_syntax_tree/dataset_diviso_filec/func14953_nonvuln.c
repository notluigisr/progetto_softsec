PHP_METHOD(imagickkernel, addkernel)
{
	zval *objvar;
	KernelInfo *kernel_info_add_clone;

	KernelInfo *kernel_info;
	KernelInfo *kernel_info_target;

	php_imagickkernel_object *kernel;
	php_imagickkernel_object *internp;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR", &objvar, php_imagickkernel_sc_entry) == FAILURE) {
		return;
	}

	kernel = Z_IMAGICKKERNEL_P(objvar);
	internp = Z_IMAGICKKERNEL_P(getThis());

	if (kernel->kernel_info == NULL) {
		zend_throw_exception(php_imagickkernel_exception_class_entry, "STR", (long)0 TSRMLS_CC);
		RETURN_NULL();
	}

	kernel_info = internp->kernel_info;
	do {
		kernel_info_target = kernel_info;
		kernel_info = kernel_info->next;
	} while (kernel_info != NULL);

	kernel_info_add_clone = CloneKernelInfo(kernel->kernel_info);
	kernel_info_target->next = kernel_info_add_clone;

	return;
}