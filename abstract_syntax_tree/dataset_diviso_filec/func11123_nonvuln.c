static int ZEND_FASTCALL  ZEND_FETCH_UNSET_SPEC_CONST_HANDLER(ZEND_OPCODE_HANDLER_ARGS)
{
	return zend_fetch_var_address_helper_SPEC_CONST(BP_VAR_UNSET, ZEND_OPCODE_HANDLER_ARGS_PASSTHRU);
}