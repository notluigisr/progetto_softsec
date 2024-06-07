static int ZEND_FASTCALL  ZEND_ASSIGN_SPEC_CV_TMP_HANDLER(ZEND_OPCODE_HANDLER_ARGS)
{
	zend_op *opline = EX(opline);
	zend_free_op free_op2;
	zval *value = _get_zval_ptr_tmp(&opline->op2, EX(Ts), &free_op2 TSRMLS_CC);
	zval **variable_ptr_ptr = _get_zval_ptr_ptr_cv(&opline->op1, EX(Ts), BP_VAR_W TSRMLS_CC);

	if (IS_CV == IS_VAR && !variable_ptr_ptr) {
		if (zend_assign_to_string_offset(&EX_T(opline->op1.u.var), value, IS_TMP_VAR TSRMLS_CC)) {
			if (!RETURN_VALUE_UNUSED(&opline->result)) {
				EX_T(opline->result.u.var).var.ptr_ptr = &EX_T(opline->result.u.var).var.ptr;
				ALLOC_ZVAL(EX_T(opline->result.u.var).var.ptr);
				INIT_PZVAL(EX_T(opline->result.u.var).var.ptr);
				ZVAL_STRINGL(EX_T(opline->result.u.var).var.ptr, Z_STRVAL_P(EX_T(opline->op1.u.var).str_offset.str)+EX_T(opline->op1.u.var).str_offset.offset, 1, 1);
			}
		} else if (!RETURN_VALUE_UNUSED(&opline->result)) {
			AI_SET_PTR(EX_T(opline->result.u.var).var, EG(uninitialized_zval_ptr));
			PZVAL_LOCK(EG(uninitialized_zval_ptr));
		}
	} else {
	 	value = zend_assign_to_variable(variable_ptr_ptr, value, 1 TSRMLS_CC);
		if (!RETURN_VALUE_UNUSED(&opline->result)) {
			AI_SET_PTR(EX_T(opline->result.u.var).var, value);
			PZVAL_LOCK(value);
		}
	}

	

	ZEND_VM_NEXT_OPCODE();
}