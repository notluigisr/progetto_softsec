static int ZEND_FASTCALL  ZEND_INIT_ARRAY_SPEC_CV_VAR_HANDLER(ZEND_OPCODE_HANDLER_ARGS)
{
	zend_op *opline = EX(opline);

	array_init(&EX_T(opline->result.u.var).tmp_var);
	if (IS_CV == IS_UNUSED) {
		ZEND_VM_NEXT_OPCODE();
#if 0 || IS_CV != IS_UNUSED
	} else {
		return ZEND_ADD_ARRAY_ELEMENT_SPEC_CV_VAR_HANDLER(ZEND_OPCODE_HANDLER_ARGS_PASSTHRU);
#endif
	}
}