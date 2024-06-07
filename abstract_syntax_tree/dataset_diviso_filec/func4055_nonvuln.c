static int ZEND_FASTCALL  ZEND_DIV_SPEC_CONST_TMP_HANDLER(ZEND_OPCODE_HANDLER_ARGS)
{
	zend_op *opline = EX(opline);
	zend_free_op free_op2;

	div_function(&EX_T(opline->result.u.var).tmp_var,
		&opline->op1.u.constant,
		_get_zval_ptr_tmp(&opline->op2, EX(Ts), &free_op2 TSRMLS_CC) TSRMLS_CC);

	zval_dtor(free_op2.var);
	ZEND_VM_NEXT_OPCODE();
}