_equalA_Indirection(const A_Indirection *a, const A_Indirection *b)
{
	COMPARE_NODE_FIELD(arg);
	COMPARE_NODE_FIELD(indirection);

	return true;
}