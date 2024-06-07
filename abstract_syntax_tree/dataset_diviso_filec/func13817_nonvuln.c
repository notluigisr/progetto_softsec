static int ZEND_FASTCALL  ZEND_INIT_FCALL_BY_NAME_SPEC_VAR_HANDLER(ZEND_OPCODE_HANDLER_ARGS)
{
	zend_op *opline = EX(opline);
	zval *function_name;
	char *function_name_strval, *lcname;
	int function_name_strlen;
	zend_free_op free_op2;

	zend_ptr_stack_3_push(&EG(arg_types_stack), EX(fbc), EX(object), EX(called_scope));

	if (IS_VAR == IS_CONST) {
		if (zend_hash_quick_find(EG(function_table), Z_STRVAL(opline->op1.u.constant), Z_STRLEN(opline->op1.u.constant)+1, opline->extended_value, (void **) &EX(fbc)) == FAILURE) {
			zend_error_noreturn(E_ERROR, "STR", Z_STRVAL(opline->op2.u.constant));
		}
	} else {
		function_name = _get_zval_ptr_var(&opline->op2, EX(Ts), &free_op2 TSRMLS_CC);

		if (IS_VAR != IS_CONST &&
		    Z_TYPE_P(function_name) == IS_OBJECT &&
			Z_OBJ_HANDLER_P(function_name, get_closure) &&
			Z_OBJ_HANDLER_P(function_name, get_closure)(function_name, &EX(called_scope), &EX(fbc), &EX(object) TSRMLS_CC) == SUCCESS) {
			if (EX(object)) {
				Z_ADDREF_P(EX(object));
			}
			if (free_op2.var) {zval_ptr_dtor(&free_op2.var);};
			ZEND_VM_NEXT_OPCODE();
		}

		if (Z_TYPE_P(function_name) != IS_STRING) {
			zend_error_noreturn(E_ERROR, "STR");
		}
		function_name_strval = Z_STRVAL_P(function_name);
		function_name_strlen = Z_STRLEN_P(function_name);
		if (function_name_strval[0] == '\\') {

		    function_name_strlen -= 1;
			lcname = zend_str_tolower_dup(function_name_strval + 1, function_name_strlen);
		} else {
			lcname = zend_str_tolower_dup(function_name_strval, function_name_strlen);
		}
		if (zend_hash_find(EG(function_table), lcname, function_name_strlen+1, (void **) &EX(fbc)) == FAILURE) {
			zend_error_noreturn(E_ERROR, "STR", function_name_strval);
		}
		efree(lcname);
		if (free_op2.var) {zval_ptr_dtor(&free_op2.var);};
	}

	EX(object) = NULL;
	ZEND_VM_NEXT_OPCODE();
}