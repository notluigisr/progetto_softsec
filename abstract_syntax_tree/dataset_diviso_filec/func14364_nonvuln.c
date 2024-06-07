static int ZEND_FASTCALL  ZEND_FETCH_OBJ_RW_SPEC_CV_CV_HANDLER(ZEND_OPCODE_HANDLER_ARGS)
{
	zend_op *opline = EX(opline);
	zend_free_op free_op1;
	zval *property = _get_zval_ptr_cv(&opline->op2, EX(Ts), BP_VAR_R TSRMLS_CC);
	zval **container = _get_zval_ptr_ptr_cv(&opline->op1, EX(Ts), BP_VAR_RW TSRMLS_CC);

	if (0) {
		MAKE_REAL_ZVAL_PTR(property);
	}
	if (IS_CV == IS_VAR && !container) {
		zend_error_noreturn(E_ERROR, "STR");
	}
	zend_fetch_property_address(&EX_T(opline->result.u.var), container, property, BP_VAR_RW TSRMLS_CC);
	if (0) {
		zval_ptr_dtor(&property);
	} else {

	}
	if (IS_CV == IS_VAR && 0 &&
	    READY_TO_DESTROY(free_op1.var)) {
		AI_USE_PTR(EX_T(opline->result.u.var).var);
		if (!PZVAL_IS_REF(*EX_T(opline->result.u.var).var.ptr_ptr) &&
		    Z_REFCOUNT_PP(EX_T(opline->result.u.var).var.ptr_ptr) > 2) {
			SEPARATE_ZVAL(EX_T(opline->result.u.var).var.ptr_ptr);
		}
	}

	ZEND_VM_NEXT_OPCODE();
}