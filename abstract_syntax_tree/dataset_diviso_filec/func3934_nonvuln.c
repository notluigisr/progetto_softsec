static int ZEND_FASTCALL  ZEND_FETCH_DIM_W_SPEC_CV_TMP_HANDLER(ZEND_OPCODE_HANDLER_ARGS)
{
	zend_op *opline = EX(opline);
	zend_free_op free_op1, free_op2;
	zval *dim = _get_zval_ptr_tmp(&opline->op2, EX(Ts), &free_op2 TSRMLS_CC);
	zval **container = _get_zval_ptr_ptr_cv(&opline->op1, EX(Ts), BP_VAR_W TSRMLS_CC);

	if (IS_CV == IS_VAR && !container) {
		zend_error_noreturn(E_ERROR, "STR");
	}
	zend_fetch_dimension_address(&EX_T(opline->result.u.var), container, dim, 1, BP_VAR_W TSRMLS_CC);
	zval_dtor(free_op2.var);
	if (IS_CV == IS_VAR && 0 &&
	    READY_TO_DESTROY(free_op1.var)) {
		AI_USE_PTR(EX_T(opline->result.u.var).var);
		if (!PZVAL_IS_REF(*EX_T(opline->result.u.var).var.ptr_ptr) &&
		    Z_REFCOUNT_PP(EX_T(opline->result.u.var).var.ptr_ptr) > 2) {
			SEPARATE_ZVAL(EX_T(opline->result.u.var).var.ptr_ptr);
		}
	}

	
	if (opline->extended_value && EX_T(opline->result.u.var).var.ptr_ptr) {
		Z_DELREF_PP(EX_T(opline->result.u.var).var.ptr_ptr);
		SEPARATE_ZVAL_TO_MAKE_IS_REF(EX_T(opline->result.u.var).var.ptr_ptr);
		Z_ADDREF_PP(EX_T(opline->result.u.var).var.ptr_ptr);
	}

	ZEND_VM_NEXT_OPCODE();
}