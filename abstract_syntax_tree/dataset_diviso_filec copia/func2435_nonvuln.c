ZEND_VM_COLD_CONSTCONST_HANDLER(93, ZEND_FETCH_DIM_FUNC_ARG, CONST|TMP|VAR|CV, CONST|TMPVAR|UNUSED|NEXT|CV)
{
#if !ZEND_VM_SPEC
	USE_OPLINE
#endif

	if (UNEXPECTED(ZEND_CALL_INFO(EX(call)) & ZEND_CALL_SEND_ARG_BY_REF)) {
        if ((OP1_TYPE & (IS_CONST|IS_TMP_VAR))) {
			ZEND_VM_DISPATCH_TO_HELPER(zend_use_tmp_in_write_context_helper);
        }
		ZEND_VM_DISPATCH_TO_HANDLER(ZEND_FETCH_DIM_W);
	} else {
		if (OP2_TYPE == IS_UNUSED) {
			ZEND_VM_DISPATCH_TO_HELPER(zend_use_undef_in_read_context_helper);
		}
		ZEND_VM_DISPATCH_TO_HANDLER(ZEND_FETCH_DIM_R);
	}
}