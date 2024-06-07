static int ZEND_FASTCALL  ZEND_JMP_SET_SPEC_CV_HANDLER(ZEND_OPCODE_HANDLER_ARGS)
{
	zend_op *opline = EX(opline);

	zval *value = _get_zval_ptr_cv(&opline->op1, EX(Ts), BP_VAR_R TSRMLS_CC);

	if (i_zend_is_true(value)) {
		EX_T(opline->result.u.var).tmp_var = *value;
		zendi_zval_copy_ctor(EX_T(opline->result.u.var).tmp_var);

#if DEBUG_ZEND>=2
		printf("STR", opline->op2.u.opline_num);
#endif
		ZEND_VM_JMP(opline->op2.u.jmp_addr);
	}

	ZEND_VM_NEXT_OPCODE();
}