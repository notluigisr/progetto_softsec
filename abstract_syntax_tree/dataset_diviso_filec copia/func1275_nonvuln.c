ZEND_VM_HANDLER(30, ZEND_ASSIGN_REF, VAR|CV, VAR|CV, SRC)
{
	USE_OPLINE
	zend_free_op free_op1, free_op2;
	zval *variable_ptr;
	zval *value_ptr;

	SAVE_OPLINE();
	value_ptr = GET_OP2_ZVAL_PTR_PTR(BP_VAR_W);
	variable_ptr = GET_OP1_ZVAL_PTR_PTR_UNDEF(BP_VAR_W);

	if (OP1_TYPE == IS_VAR && UNEXPECTED(Z_ISERROR_P(variable_ptr))) {
		variable_ptr = &EG(uninitialized_zval);
	} else if (OP1_TYPE == IS_VAR &&
	           UNEXPECTED(Z_TYPE_P(EX_VAR(opline->op1.var)) != IS_INDIRECT)) {

		zend_throw_error(NULL, "STR");
		variable_ptr = &EG(uninitialized_zval);
	} else if (OP2_TYPE == IS_VAR && UNEXPECTED(Z_ISERROR_P(value_ptr))) {
		variable_ptr = &EG(uninitialized_zval);
	} else if (OP2_TYPE == IS_VAR &&
	           opline->extended_value == ZEND_RETURNS_FUNCTION &&
			   UNEXPECTED(!Z_ISREF_P(value_ptr))) {

		variable_ptr = zend_wrong_assign_to_variable_reference(
			variable_ptr, value_ptr OPLINE_CC EXECUTE_DATA_CC);
	} else {
		zend_assign_to_variable_reference(variable_ptr, value_ptr);
	}

	if (UNEXPECTED(RETURN_VALUE_USED(opline))) {
		ZVAL_COPY(EX_VAR(opline->result.var), variable_ptr);
	}

	FREE_OP2_VAR_PTR();
	FREE_OP1_VAR_PTR();
	ZEND_VM_NEXT_OPCODE_CHECK_EXCEPTION();
}