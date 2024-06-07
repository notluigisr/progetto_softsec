static int ZEND_FASTCALL  ZEND_ADD_ARRAY_ELEMENT_SPEC_CV_UNUSED_HANDLER(ZEND_OPCODE_HANDLER_ARGS)
{
	zend_op *opline = EX(opline);

	zval *array_ptr = &EX_T(opline->result.u.var).tmp_var;
	zval *expr_ptr;
	zval *offset=NULL;

#if 0 || IS_CV == IS_VAR || IS_CV == IS_CV
	zval **expr_ptr_ptr = NULL;

	if (opline->extended_value) {
		expr_ptr_ptr=_get_zval_ptr_ptr_cv(&opline->op1, EX(Ts), BP_VAR_W TSRMLS_CC);
		expr_ptr = *expr_ptr_ptr;
	} else {
		expr_ptr=_get_zval_ptr_cv(&opline->op1, EX(Ts), BP_VAR_R TSRMLS_CC);
	}
#else
	expr_ptr=_get_zval_ptr_cv(&opline->op1, EX(Ts), BP_VAR_R TSRMLS_CC);
#endif

	if (0) { 
		zval *new_expr;

		ALLOC_ZVAL(new_expr);
		INIT_PZVAL_COPY(new_expr, expr_ptr);
		expr_ptr = new_expr;
	} else {
#if 0 || IS_CV == IS_VAR || IS_CV == IS_CV
		if (opline->extended_value) {
			SEPARATE_ZVAL_TO_MAKE_IS_REF(expr_ptr_ptr);
			expr_ptr = *expr_ptr_ptr;
			Z_ADDREF_P(expr_ptr);
		} else
#endif
		if (IS_CV == IS_CONST || PZVAL_IS_REF(expr_ptr)) {
			zval *new_expr;

			ALLOC_ZVAL(new_expr);
			INIT_PZVAL_COPY(new_expr, expr_ptr);
			expr_ptr = new_expr;
			zendi_zval_copy_ctor(*expr_ptr);
		} else {
			Z_ADDREF_P(expr_ptr);
		}
	}
	if (offset) {
		switch (Z_TYPE_P(offset)) {
			case IS_DOUBLE:
				zend_hash_index_update(Z_ARRVAL_P(array_ptr), zend_dval_to_lval(Z_DVAL_P(offset)), &expr_ptr, sizeof(zval *), NULL);
				break;
			case IS_LONG:
			case IS_BOOL:
				zend_hash_index_update(Z_ARRVAL_P(array_ptr), Z_LVAL_P(offset), &expr_ptr, sizeof(zval *), NULL);
				break;
			case IS_STRING:
				zend_symtable_update(Z_ARRVAL_P(array_ptr), Z_STRVAL_P(offset), Z_STRLEN_P(offset)+1, &expr_ptr, sizeof(zval *), NULL);
				break;
			case IS_NULL:
				zend_hash_update(Z_ARRVAL_P(array_ptr), "STR"), &expr_ptr, sizeof(zval *), NULL);
				break;
			default:
				zend_error(E_WARNING, "STR");
				zval_ptr_dtor(&expr_ptr);
				
				break;
		}

	} else {
		zend_hash_next_index_insert(Z_ARRVAL_P(array_ptr), &expr_ptr, sizeof(zval *), NULL);
	}
	if (opline->extended_value) {

	} else {

	}
	ZEND_VM_NEXT_OPCODE();
}