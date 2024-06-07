static int ZEND_FASTCALL  ZEND_SL_SPEC_TMP_CV_HANDLER(ZEND_OPCODE_HANDLER_ARGS)
{
	zend_op *opline = EX(opline);
	zend_free_op free_op1;

	shift_left_function(&EX_T(opline->result.u.var).tmp_var,
		_get_zval_ptr_tmp(&opline->op1, EX(Ts), &free_op1 TSRMLS_CC),
		_get_zval_ptr_cv(&opline->op2, EX(Ts), BP_VAR_R TSRMLS_CC) TSRMLS_CC);
	zval_dtor(free_op1.var);

	ZEND_VM_NEXT_OPCODE();
}