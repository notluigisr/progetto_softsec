static int ZEND_FASTCALL  ZEND_INIT_ARRAY_SPEC_TMP_CONST_HANDLER(ZEND_OPCODE_HANDLER_ARGS)
{
	zend_op *opline = EX(opline);

	array_init(&EX_T(opline->result.u.var).tmp_var);
	if (IS_TMP_VAR == IS_UNUSED) {
		ZEND_VM_NEXT_OPCODE();
#if 0 || IS_TMP_VAR != IS_UNUSED
	} else {
		return ZEND_ADD_ARRAY_ELEMENT_SPEC_TMP_CONST_HANDLER(ZEND_OPCODE_HANDLER_ARGS_PASSTHRU);
#endif
	}
}