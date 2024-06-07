_equalTransactionStmt(const TransactionStmt *a, const TransactionStmt *b)
{
	COMPARE_SCALAR_FIELD(kind);
	COMPARE_NODE_FIELD(options);
	COMPARE_STRING_FIELD(gid);

	return true;
}