ZEND_VM_HELPER(zend_sub_helper, ANY, ANY, zval *op_1, zval *op_2)
{
	USE_OPLINE

	SAVE_OPLINE();
	if (UNEXPECTED(Z_TYPE_INFO_P(op_1) == IS_UNDEF)) {
		op_1 = ZVAL_UNDEFINED_OP1();
	}
	if (UNEXPECTED(Z_TYPE_INFO_P(op_2) == IS_UNDEF)) {
		op_2 = ZVAL_UNDEFINED_OP2();
	}
	sub_function(EX_VAR(opline->result.var), op_1, op_2);
	if (OP1_TYPE & (IS_TMP_VAR|IS_VAR)) {
		zval_ptr_dtor_nogc(op_1);
	}
	if (OP2_TYPE & (IS_TMP_VAR|IS_VAR)) {
		zval_ptr_dtor_nogc(op_2);
	}
	ZEND_VM_NEXT_OPCODE_CHECK_EXCEPTION();
}