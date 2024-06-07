static void zend_generator_dtor_storage(zend_object *object) 
{
	zend_generator *generator = (zend_generator*) object;
	zend_execute_data *ex = generator->execute_data;
	uint32_t op_num, finally_op_num, finally_op_end;
	int i;

	
	if (UNEXPECTED(Z_TYPE(generator->values) != IS_UNDEF)) {
		zval_ptr_dtor(&generator->values);
		ZVAL_UNDEF(&generator->values);
	}

	if (EXPECTED(generator->node.children == 0)) {
		zend_generator *root = generator->node.ptr.root, *next;
		while (UNEXPECTED(root != generator)) {
			next = zend_generator_get_child(&root->node, generator);
			generator->node.ptr.root = next;
			next->node.parent = NULL;
			OBJ_RELEASE(&root->std);
			root = next;
		}
	}

	if (EXPECTED(!ex) || EXPECTED(!(ex->func->op_array.fn_flags & ZEND_ACC_HAS_FINALLY_BLOCK))
			|| CG(unclean_shutdown)) {
		return;
	}

	
	op_num = ex->opline - ex->func->op_array.opcodes - 1;

	
	finally_op_num = 0;
	finally_op_end = 0;
	for (i = 0; i < ex->func->op_array.last_try_catch; i++) {
		zend_try_catch_element *try_catch = &ex->func->op_array.try_catch_array[i];

		if (op_num < try_catch->try_op) {
			break;
		}

		if (op_num < try_catch->finally_op) {
			finally_op_num = try_catch->finally_op;
			finally_op_end = try_catch->finally_end;
		}
	}

	
	if (finally_op_num) {
		zval *fast_call;

		zend_generator_cleanup_unfinished_execution(generator, finally_op_num);

		fast_call = ZEND_CALL_VAR(ex, ex->func->op_array.opcodes[finally_op_end].op1.var);
		Z_OBJ_P(fast_call) = EG(exception);
		EG(exception) = NULL;
		fast_call->u2.lineno = (uint32_t)-1;

		ex->opline = &ex->func->op_array.opcodes[finally_op_num];
		generator->flags |= ZEND_GENERATOR_FORCED_CLOSE;
		zend_generator_resume(generator);
	}
}