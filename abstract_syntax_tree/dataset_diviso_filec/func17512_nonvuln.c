_equalJoinExpr(const JoinExpr *a, const JoinExpr *b)
{
	COMPARE_SCALAR_FIELD(jointype);
	COMPARE_SCALAR_FIELD(isNatural);
	COMPARE_NODE_FIELD(larg);
	COMPARE_NODE_FIELD(rarg);
	COMPARE_NODE_FIELD(usingClause);
	COMPARE_NODE_FIELD(quals);
	COMPARE_NODE_FIELD(alias);
	COMPARE_SCALAR_FIELD(rtindex);

	return true;
}