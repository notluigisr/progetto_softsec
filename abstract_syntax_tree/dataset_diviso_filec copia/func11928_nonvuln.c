get_call_expr_argtype(Node *expr, int argnum)
{
	List	   *args;
	Oid			argtype;

	if (expr == NULL)
		return InvalidOid;

	if (IsA(expr, FuncExpr))
		args = ((FuncExpr *) expr)->args;
	else if (IsA(expr, OpExpr))
		args = ((OpExpr *) expr)->args;
	else if (IsA(expr, DistinctExpr))
		args = ((DistinctExpr *) expr)->args;
	else if (IsA(expr, ScalarArrayOpExpr))
		args = ((ScalarArrayOpExpr *) expr)->args;
	else if (IsA(expr, ArrayCoerceExpr))
		args = list_make1(((ArrayCoerceExpr *) expr)->arg);
	else if (IsA(expr, NullIfExpr))
		args = ((NullIfExpr *) expr)->args;
	else if (IsA(expr, WindowFunc))
		args = ((WindowFunc *) expr)->args;
	else
		return InvalidOid;

	if (argnum < 0 || argnum >= list_length(args))
		return InvalidOid;

	argtype = exprType((Node *) list_nth(args, argnum));

	
	if (IsA(expr, ScalarArrayOpExpr) &&
		argnum == 1)
		argtype = get_base_element_type(argtype);
	else if (IsA(expr, ArrayCoerceExpr) &&
			 argnum == 0)
		argtype = get_base_element_type(argtype);

	return argtype;
}