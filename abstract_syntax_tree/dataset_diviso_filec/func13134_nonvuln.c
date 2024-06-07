ZEND_VM_HANDLER(151, ZEND_ASSERT_CHECK, ANY, JMP_ADDR)
{
	USE_OPLINE

	if (EG(assertions) <= 0) {
		zend_op *target = OP_JMP_ADDR(opline, opline->op2);
		if (RETURN_VALUE_USED(opline)) {
			ZVAL_TRUE(EX_VAR(opline->result.var));
		}
		ZEND_VM_JMP_EX(target, 0);
	} else {
		ZEND_VM_NEXT_OPCODE();
	}
}