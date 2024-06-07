static int ZEND_FASTCALL  ZEND_IS_IDENTICAL_SPEC_CONST_VAR_HANDLER(ZEND_OPCODE_HANDLER_ARGS)
{
	zend_op *opline = EX(opline);
	zend_free_op free_op2;

	is_identical_function(&EX_T(opline->result.u.var).tmp_var,
		&opline->op1.u.constant,
		_get_zval_ptr_var(&opline->op2, EX(Ts), &free_op2 TSRMLS_CC) TSRMLS_CC);

	if (free_op2.var) {zval_ptr_dtor(&free_op2.var);};
	ZEND_VM_NEXT_OPCODE();
}