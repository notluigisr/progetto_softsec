_equalColumnRef(const ColumnRef *a, const ColumnRef *b)
{
	COMPARE_NODE_FIELD(fields);
	COMPARE_LOCATION_FIELD(location);

	return true;
}