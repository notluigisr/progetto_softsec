static int __cil_evaluate_tunable_expr(struct cil_list_item *curr)
{
	

	if (curr == NULL) {
		return CIL_FALSE;
	} else if (curr->flavor == CIL_OP) {
		uint16_t v1, v2;
		enum cil_flavor op_flavor = (enum cil_flavor)(uintptr_t)curr->data;

		v1 = __cil_evaluate_tunable_expr_helper(curr->next);

		if (op_flavor == CIL_NOT) return !v1;

		v2 = __cil_evaluate_tunable_expr_helper(curr->next->next);

		if (op_flavor == CIL_AND) return (v1 && v2);
		else if (op_flavor == CIL_OR) return (v1 || v2);
		else if (op_flavor == CIL_XOR) return (v1 ^ v2);
		else if (op_flavor == CIL_EQ) return (v1 == v2);
		else if (op_flavor == CIL_NEQ) return (v1 != v2);
		else return CIL_FALSE;
	} else {
		uint16_t v;
		for (;curr; curr = curr->next) {
			v = __cil_evaluate_tunable_expr_helper(curr);
			if (v) return v;
		}
		return CIL_FALSE;
	}
}