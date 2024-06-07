_outTidScan(StringInfo str, const TidScan *node)
{
	WRITE_NODE_TYPE("STR");

	_outScanInfo(str, (const Scan *) node);

	WRITE_NODE_FIELD(tidquals);
}