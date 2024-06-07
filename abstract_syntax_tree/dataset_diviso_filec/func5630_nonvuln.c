static int ZEND_FASTCALL  ZEND_ADD_SPEC_CONST_CV_HANDLER(ZEND_OPCODE_HANDLER_ARGS)
{
	zend_op *opline = EX(opline);


	add_function(&EX_T(opline->result.u.var).tmp_var,
		&opline->op1.u.constant,
		_get_zval_ptr_cv(&opline->op2, EX(Ts), BP_VAR_R TSRMLS_CC) TSRMLS_CC);


	ZEND_VM_NEXT_OPCODE();
}