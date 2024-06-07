_equalSortGroupClause(const SortGroupClause *a, const SortGroupClause *b)
{
	COMPARE_SCALAR_FIELD(tleSortGroupRef);
	COMPARE_SCALAR_FIELD(eqop);
	COMPARE_SCALAR_FIELD(sortop);
	COMPARE_SCALAR_FIELD(nulls_first);
	COMPARE_SCALAR_FIELD(hashable);

	return true;
}