 Default implementation for __autoload() */
PHP_FUNCTION(spl_autoload)
{
	char *class_name, *lc_name, *file_exts = SPL_G(autoload_extensions);
	int class_name_len, file_exts_len = SPL_G(autoload_extensions_len), found = 0;
	char *copy, *pos1, *pos2;
	zval **original_return_value = EG(return_value_ptr_ptr);
	zend_op **original_opline_ptr = EG(opline_ptr);
	zend_op_array *original_active_op_array = EG(active_op_array);
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR", &class_name, &class_name_len, &file_exts, &file_exts_len) == FAILURE) {
		RETURN_FALSE;
	}

	if (file_exts == NULL) { 
		copy = pos1 = estrndup(SPL_DEFAULT_FILE_EXTENSIONS, sizeof(SPL_DEFAULT_FILE_EXTENSIONS)-1);
	} else {
		copy = pos1 = estrndup(file_exts, file_exts_len);
	}
	lc_name = zend_str_tolower_dup(class_name, class_name_len);
	while(pos1 && *pos1 && !EG(exception)) {
		EG(return_value_ptr_ptr) = original_return_value;
		EG(opline_ptr) = original_opline_ptr;
		EG(active_op_array) = original_active_op_array;
		pos2 = strchr(pos1, ',');
		if (pos2) *pos2 = '\0';
		if (spl_autoload(class_name, lc_name, class_name_len, pos1 TSRMLS_CC)) {
			found = 1;
			break; 
		}
		pos1 = pos2 ? pos2 + 1 : NULL;
	}
	efree(lc_name);
	if (copy) {
		efree(copy);
	}

	EG(return_value_ptr_ptr) = original_return_value;
	EG(opline_ptr) = original_opline_ptr;
	EG(active_op_array) = original_active_op_array;

	if (!found && !SPL_G(autoload_running)) {
		
		if (active_opline->opcode != ZEND_FETCH_CLASS) {
			zend_throw_exception_ex(spl_ce_LogicException, 0 TSRMLS_CC, "STR", class_name);
		} else {
			php_error_docref(NULL TSRMLS_CC, E_ERROR, "STR", class_name);
		}
	}