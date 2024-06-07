static int ZEND_FASTCALL  ZEND_ASSIGN_OBJ_SPEC_VAR_TMP_HANDLER(ZEND_OPCODE_HANDLER_ARGS)
{
	zend_op *opline = EX(opline);
	zend_op *op_data = opline+1;
	zend_free_op free_op1, free_op2;
	zval **object_ptr = _get_zval_ptr_ptr_var(&opline->op1, EX(Ts), &free_op1 TSRMLS_CC);
	zval *property_name = _get_zval_ptr_tmp(&opline->op2, EX(Ts), &free_op2 TSRMLS_CC);

	if (1) {
		MAKE_REAL_ZVAL_PTR(property_name);
	}
	if (IS_VAR == IS_VAR && !object_ptr) {
		zend_error_noreturn(E_ERROR, "STR");
	}
	zend_assign_to_object(&opline->result, object_ptr, property_name, &op_data->op1, EX(Ts), ZEND_ASSIGN_OBJ TSRMLS_CC);
	if (1) {
		zval_ptr_dtor(&property_name);
	} else {
		zval_dtor(free_op2.var);
	}
	if (free_op1.var) {zval_ptr_dtor(&free_op1.var);};
	
	ZEND_VM_INC_OPCODE();
	ZEND_VM_NEXT_OPCODE();
}