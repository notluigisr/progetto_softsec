_outBooleanTest(StringInfo str, const BooleanTest *node)
{
	WRITE_NODE_TYPE("STR");

	WRITE_NODE_FIELD(arg);
	WRITE_ENUM_FIELD(booltesttype, BoolTestType);
}