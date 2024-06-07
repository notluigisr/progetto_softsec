ZEND_VM_HOT_HANDLER(122, ZEND_DEFINED, CONST, ANY, CACHE_SLOT)
{
	USE_OPLINE
	zend_constant *c;

	c = CACHED_PTR(opline->extended_value);
	if (EXPECTED(c != NULL)) {
		if (!IS_SPECIAL_CACHE_VAL(c)) {
ZEND_VM_C_LABEL(defined_true):
			ZEND_VM_SMART_BRANCH_TRUE();
			ZVAL_TRUE(EX_VAR(opline->result.var));
			ZEND_VM_NEXT_OPCODE();
		} else if (EXPECTED(zend_hash_num_elements(EG(zend_constants)) == DECODE_SPECIAL_CACHE_NUM(c))) {
ZEND_VM_C_LABEL(defined_false):
			ZEND_VM_SMART_BRANCH_FALSE();
			ZVAL_FALSE(EX_VAR(opline->result.var));
			ZEND_VM_NEXT_OPCODE();
		}
	}
	if (zend_quick_check_constant(RT_CONSTANT(opline, opline->op1) OPLINE_CC EXECUTE_DATA_CC) != SUCCESS) {
		CACHE_PTR(opline->extended_value, ENCODE_SPECIAL_CACHE_NUM(zend_hash_num_elements(EG(zend_constants))));
		ZEND_VM_C_GOTO(defined_false);
	} else {
		ZEND_VM_C_GOTO(defined_true);
	}
}