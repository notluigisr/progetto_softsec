ZEND_VM_COLD_CONST_HANDLER(152, ZEND_JMP_SET, CONST|TMP|VAR|CV, JMP_ADDR)
{
	USE_OPLINE
	zend_free_op free_op1;
	zval *value;
	zval *ref = NULL;
	int ret;

	SAVE_OPLINE();
	value = GET_OP1_ZVAL_PTR(BP_VAR_R);

	if ((OP1_TYPE == IS_VAR || OP1_TYPE == IS_CV) && Z_ISREF_P(value)) {
		if (OP1_TYPE == IS_VAR) {
			ref = value;
		}
		value = Z_REFVAL_P(value);
	}

	ret = i_zend_is_true(value);

	if (UNEXPECTED(EG(exception))) {
		FREE_OP1();
		ZVAL_UNDEF(EX_VAR(opline->result.var));
		HANDLE_EXCEPTION();
	}

	if (ret) {
		zval *result = EX_VAR(opline->result.var);

		ZVAL_COPY_VALUE(result, value);
		if (OP1_TYPE == IS_CONST) {
			if (UNEXPECTED(Z_OPT_REFCOUNTED_P(result))) Z_ADDREF_P(result);
		} else if (OP1_TYPE == IS_CV) {
			if (Z_OPT_REFCOUNTED_P(result)) Z_ADDREF_P(result);
		} else if (OP1_TYPE == IS_VAR && ref) {
			zend_reference *r = Z_REF_P(ref);

			if (UNEXPECTED(GC_DELREF(r) == 0)) {
				efree_size(r, sizeof(zend_reference));
			} else if (Z_OPT_REFCOUNTED_P(result)) {
				Z_ADDREF_P(result);
			}
		}
		ZEND_VM_JMP_EX(OP_JMP_ADDR(opline, opline->op2), 0);
	}

	FREE_OP1();
	ZEND_VM_NEXT_OPCODE();
}