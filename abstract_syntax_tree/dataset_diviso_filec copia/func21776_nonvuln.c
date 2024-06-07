static enum cil_flavor __cil_get_constraint_operator_flavor(const char *op)
{
	if (op == CIL_KEY_AND)         return CIL_AND;
	else if (op == CIL_KEY_OR)     return CIL_OR;
	else if (op == CIL_KEY_NOT)    return CIL_NOT;
	else if (op == CIL_KEY_EQ)     return CIL_EQ;
	else if (op == CIL_KEY_NEQ)    return CIL_NEQ;
	else if (op == CIL_KEY_CONS_DOM)    return CIL_CONS_DOM;
	else if (op == CIL_KEY_CONS_DOMBY)  return CIL_CONS_DOMBY;
	else if (op == CIL_KEY_CONS_INCOMP) return CIL_CONS_INCOMP;
	else return CIL_NONE;
}