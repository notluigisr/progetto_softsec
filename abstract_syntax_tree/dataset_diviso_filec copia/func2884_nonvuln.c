_outTypeCast(StringInfo str, const TypeCast *node)
{
	WRITE_NODE_TYPE("STR");

	WRITE_NODE_FIELD(arg);
	WRITE_NODE_FIELD(typeName);
	WRITE_LOCATION_FIELD(location);
}