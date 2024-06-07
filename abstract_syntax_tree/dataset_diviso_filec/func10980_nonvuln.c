static int ZEND_FASTCALL  ZEND_CASE_SPEC_VAR_CV_HANDLER(ZEND_OPCODE_HANDLER_ARGS)
{
	zend_op *opline = EX(opline);
	int switch_expr_is_overloaded=0;
	zend_free_op free_op1;

	if (IS_VAR==IS_VAR) {
		if (EX_T(opline->op1.u.var).var.ptr_ptr) {
			PZVAL_LOCK(EX_T(opline->op1.u.var).var.ptr);
		} else {
			switch_expr_is_overloaded = 1;
			Z_ADDREF_P(EX_T(opline->op1.u.var).str_offset.str);
		}
	}
	is_equal_function(&EX_T(opline->result.u.var).tmp_var,
				 _get_zval_ptr_var(&opline->op1, EX(Ts), &free_op1 TSRMLS_CC),
				 _get_zval_ptr_cv(&opline->op2, EX(Ts), BP_VAR_R TSRMLS_CC) TSRMLS_CC);

	if (switch_expr_is_overloaded) {
		
		if (free_op1.var) {zval_ptr_dtor(&free_op1.var);};
		EX_T(opline->op1.u.var).var.ptr_ptr = NULL;
		EX_T(opline->op1.u.var).var.ptr = NULL;
	}
	ZEND_VM_NEXT_OPCODE();
}