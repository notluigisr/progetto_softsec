ZEND_VM_COLD_CONSTCONST_HANDLER(188, ZEND_SWITCH_STRING, CONST|TMPVARCV, CONST, JMP_ADDR)
{
	USE_OPLINE
	zend_free_op free_op1, free_op2;
	zval *op, *jump_zv;
	HashTable *jumptable;

	op = GET_OP1_ZVAL_PTR_UNDEF(BP_VAR_R);
	jumptable = Z_ARRVAL_P(GET_OP2_ZVAL_PTR(BP_VAR_R));

	if (Z_TYPE_P(op) != IS_STRING) {
		if (OP1_TYPE == IS_CONST) {
			
			ZEND_VM_NEXT_OPCODE();
		} else {
			ZVAL_DEREF(op);
			if (Z_TYPE_P(op) != IS_STRING) {
				
				ZEND_VM_NEXT_OPCODE();
			}
		}
	}

	jump_zv = zend_hash_find_ex(jumptable, Z_STR_P(op), OP1_TYPE == IS_CONST);
	if (jump_zv != NULL) {
		ZEND_VM_SET_RELATIVE_OPCODE(opline, Z_LVAL_P(jump_zv));
		ZEND_VM_CONTINUE();
	} else {
		
		ZEND_VM_SET_RELATIVE_OPCODE(opline, opline->extended_value);
		ZEND_VM_CONTINUE();
	}
}