parse_wcc_attr(netdissect_options *ndo,
               const uint32_t *dp)
{
	ND_PRINT((ndo, "STR" PRIu64, EXTRACT_64BITS(&dp[0])));
	ND_PRINT((ndo, "STR",
	       EXTRACT_32BITS(&dp[2]), EXTRACT_32BITS(&dp[3]),
	       EXTRACT_32BITS(&dp[4]), EXTRACT_32BITS(&dp[5])));
	return (dp + 6);
}