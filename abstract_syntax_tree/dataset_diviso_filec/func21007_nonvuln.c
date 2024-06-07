_outForeignScan(StringInfo str, const ForeignScan *node)
{
	WRITE_NODE_TYPE("STR");

	_outScanInfo(str, (const Scan *) node);

	WRITE_NODE_FIELD(fdw_exprs);
	WRITE_NODE_FIELD(fdw_private);
	WRITE_BOOL_FIELD(fsSystemCol);
}