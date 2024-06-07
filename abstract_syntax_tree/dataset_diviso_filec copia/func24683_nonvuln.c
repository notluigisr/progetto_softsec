_equalTruncateStmt(const TruncateStmt *a, const TruncateStmt *b)
{
	COMPARE_NODE_FIELD(relations);
	COMPARE_SCALAR_FIELD(restart_seqs);
	COMPARE_SCALAR_FIELD(behavior);

	return true;
}