ZEND_VM_HANDLER(172, ZEND_FUNC_GET_ARGS, UNUSED|CONST, UNUSED)
{
	USE_OPLINE
	zend_array *ht;
	uint32_t arg_count, result_size, skip;

	arg_count = EX_NUM_ARGS();
	if (OP1_TYPE == IS_CONST) {
		skip = Z_LVAL_P(RT_CONSTANT(opline, opline->op1));
		if (arg_count < skip) {
			result_size = 0;
		} else {
			result_size = arg_count - skip;
		}
	} else {
		skip = 0;
		result_size = arg_count;
	}

	if (result_size) {
		uint32_t first_extra_arg = EX(func)->op_array.num_args;

		ht = zend_new_array(result_size);
		ZVAL_ARR(EX_VAR(opline->result.var), ht);
		zend_hash_real_init_packed(ht);
		ZEND_HASH_FILL_PACKED(ht) {
			zval *p, *q;
			uint32_t i = skip;
			p = EX_VAR_NUM(i);
			if (arg_count > first_extra_arg) {
				while (i < first_extra_arg) {
					q = p;
					if (EXPECTED(Z_TYPE_INFO_P(q) != IS_UNDEF)) {
						ZVAL_DEREF(q);
						if (Z_OPT_REFCOUNTED_P(q)) {
							Z_ADDREF_P(q);
						}
						ZEND_HASH_FILL_SET(q);
					} else {
						ZEND_HASH_FILL_SET_NULL();
					}
					ZEND_HASH_FILL_NEXT();
					p++;
					i++;
				}
				if (skip < first_extra_arg) {
					skip = 0;
				} else {
					skip -= first_extra_arg;
				}
				p = EX_VAR_NUM(EX(func)->op_array.last_var + EX(func)->op_array.T + skip);
			}
			while (i < arg_count) {
				q = p;
				if (EXPECTED(Z_TYPE_INFO_P(q) != IS_UNDEF)) {
					ZVAL_DEREF(q);
					if (Z_OPT_REFCOUNTED_P(q)) {
						Z_ADDREF_P(q);
					}
					ZEND_HASH_FILL_SET(q);
				} else {
					ZEND_HASH_FILL_SET_NULL();
				}
				ZEND_HASH_FILL_NEXT();
				p++;
				i++;
			}
		} ZEND_HASH_FILL_END();
		ht->nNumOfElements = result_size;
	} else {
		ZVAL_EMPTY_ARRAY(EX_VAR(opline->result.var));
	}
	ZEND_VM_NEXT_OPCODE();
}