static int ZEND_FASTCALL  ZEND_SEND_VAL_SPEC_CONST_HANDLER(ZEND_OPCODE_HANDLER_ARGS)
{
	zend_op *opline = EX(opline);
	if (opline->extended_value==ZEND_DO_FCALL_BY_NAME
		&& ARG_MUST_BE_SENT_BY_REF(EX(fbc), opline->op2.u.opline_num)) {
			zend_error_noreturn(E_ERROR, "STR", opline->op2.u.opline_num);
	}
	{
		zval *valptr;
		zval *value;


		value = &opline->op1.u.constant;

		ALLOC_ZVAL(valptr);
		INIT_PZVAL_COPY(valptr, value);
		if (!0) {
			zval_copy_ctor(valptr);
		}
		zend_vm_stack_push(valptr TSRMLS_CC);

	}
	ZEND_VM_NEXT_OPCODE();
}