_outPath(StringInfo str, const Path *node)
{
	WRITE_NODE_TYPE("STR");

	_outPathInfo(str, (const Path *) node);
}