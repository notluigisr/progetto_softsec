static int hns_gmac_get_sset_count(int stringset)
{
	if (stringset == ETH_SS_STATS)
		return ARRAY_SIZE(g_gmac_stats_string);

	return 0;
}