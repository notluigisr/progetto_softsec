_equalWithClause(const WithClause *a, const WithClause *b)
{
	COMPARE_NODE_FIELD(ctes);
	COMPARE_SCALAR_FIELD(recursive);
	COMPARE_LOCATION_FIELD(location);

	return true;
}