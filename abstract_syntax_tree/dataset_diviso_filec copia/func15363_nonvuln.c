ZEND_VM_HANDLER(58, ZEND_END_SILENCE, TMP, ANY)
{
	USE_OPLINE

	if (!EG(error_reporting) && Z_LVAL_P(EX_VAR(opline->op1.var)) != 0) {
		EG(error_reporting) = Z_LVAL_P(EX_VAR(opline->op1.var));
	}
	ZEND_VM_NEXT_OPCODE();
}