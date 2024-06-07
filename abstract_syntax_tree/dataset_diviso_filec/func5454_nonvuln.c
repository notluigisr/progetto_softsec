static int ZEND_FASTCALL  ZEND_CAST_SPEC_VAR_HANDLER(ZEND_OPCODE_HANDLER_ARGS)
{
	zend_op *opline = EX(opline);
	zend_free_op free_op1;
	zval *expr = _get_zval_ptr_var(&opline->op1, EX(Ts), &free_op1 TSRMLS_CC);
	zval *result = &EX_T(opline->result.u.var).tmp_var;

	if (opline->extended_value != IS_STRING) {
		*result = *expr;
		if (!0) {
			zendi_zval_copy_ctor(*result);
		}
	}
	switch (opline->extended_value) {
		case IS_NULL:
			convert_to_null(result);
			break;
		case IS_BOOL:
			convert_to_boolean(result);
			break;
		case IS_LONG:
			convert_to_long(result);
			break;
		case IS_DOUBLE:
			convert_to_double(result);
			break;
		case IS_STRING: {
			zval var_copy;
			int use_copy;

			zend_make_printable_zval(expr, &var_copy, &use_copy);
			if (use_copy) {
				*result = var_copy;
				if (0) {
					if (free_op1.var) {zval_ptr_dtor(&free_op1.var);};
				}
			} else {
				*result = *expr;
				if (!0) {
					zendi_zval_copy_ctor(*result);
				}
			}
			break;
		}
		case IS_ARRAY:
			convert_to_array(result);
			break;
		case IS_OBJECT:
			convert_to_object(result);
			break;
	}
	if (free_op1.var) {zval_ptr_dtor(&free_op1.var);};
	ZEND_VM_NEXT_OPCODE();
}