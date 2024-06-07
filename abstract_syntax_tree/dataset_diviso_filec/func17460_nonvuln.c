static int ZEND_FASTCALL  ZEND_FETCH_DIM_UNSET_SPEC_CV_CONST_HANDLER(ZEND_OPCODE_HANDLER_ARGS)
{
	zend_op *opline = EX(opline);
	zend_free_op free_op1;
	zval **container = _get_zval_ptr_ptr_cv(&opline->op1, EX(Ts), BP_VAR_UNSET TSRMLS_CC);
	zval *dim = &opline->op2.u.constant;

	
	if (IS_CV == IS_CV) {
		if (container != &EG(uninitialized_zval_ptr)) {
			SEPARATE_ZVAL_IF_NOT_REF(container);
		}
	}
	if (IS_CV == IS_VAR && !container) {
		zend_error_noreturn(E_ERROR, "STR");
	}
	zend_fetch_dimension_address(&EX_T(opline->result.u.var), container, dim, 0, BP_VAR_UNSET TSRMLS_CC);

	if (IS_CV == IS_VAR && 0 &&
	    READY_TO_DESTROY(free_op1.var)) {
		AI_USE_PTR(EX_T(opline->result.u.var).var);
		if (!PZVAL_IS_REF(*EX_T(opline->result.u.var).var.ptr_ptr) &&
		    Z_REFCOUNT_PP(EX_T(opline->result.u.var).var.ptr_ptr) > 2) {
			SEPARATE_ZVAL(EX_T(opline->result.u.var).var.ptr_ptr);
		}
	}

	if (EX_T(opline->result.u.var).var.ptr_ptr == NULL) {
		zend_error_noreturn(E_ERROR, "STR");
	} else {
		zend_free_op free_res;

		PZVAL_UNLOCK(*EX_T(opline->result.u.var).var.ptr_ptr, &free_res);
		if (EX_T(opline->result.u.var).var.ptr_ptr != &EG(uninitialized_zval_ptr)) {
			SEPARATE_ZVAL_IF_NOT_REF(EX_T(opline->result.u.var).var.ptr_ptr);
		}
		PZVAL_LOCK(*EX_T(opline->result.u.var).var.ptr_ptr);
		FREE_OP_VAR_PTR(free_res);
	}
	ZEND_VM_NEXT_OPCODE();
}