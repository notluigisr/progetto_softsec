static int ZEND_FASTCALL  ZEND_SL_SPEC_CV_CV_HANDLER(ZEND_OPCODE_HANDLER_ARGS)
{
	zend_op *opline = EX(opline);


	shift_left_function(&EX_T(opline->result.u.var).tmp_var,
		_get_zval_ptr_cv(&opline->op1, EX(Ts), BP_VAR_R TSRMLS_CC),
		_get_zval_ptr_cv(&opline->op2, EX(Ts), BP_VAR_R TSRMLS_CC) TSRMLS_CC);


	ZEND_VM_NEXT_OPCODE();
}