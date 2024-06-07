static int ZEND_FASTCALL  ZEND_ADD_SPEC_CV_CONST_HANDLER(ZEND_OPCODE_HANDLER_ARGS)
{
	zend_op *opline = EX(opline);


	add_function(&EX_T(opline->result.u.var).tmp_var,
		_get_zval_ptr_cv(&opline->op1, EX(Ts), BP_VAR_R TSRMLS_CC),
		&opline->op2.u.constant TSRMLS_CC);


	ZEND_VM_NEXT_OPCODE();
}