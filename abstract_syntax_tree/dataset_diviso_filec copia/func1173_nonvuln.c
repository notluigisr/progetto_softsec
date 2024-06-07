void ntlm_print_av_pair_list(NTLM_AV_PAIR* pAvPairList, size_t cbAvPairList)
{
	UINT16 pair;
	size_t cbAvPair = cbAvPairList;
	NTLM_AV_PAIR* pAvPair = pAvPairList;

	if (!ntlm_av_pair_check(pAvPair, cbAvPair))
		return;

	WLog_INFO(TAG, "STR");

	while (pAvPair && ntlm_av_pair_get_id(pAvPair, cbAvPair, &pair) && (pair != MsvAvEOL))
	{
		size_t cbLen = 0;
		ntlm_av_pair_get_len(pAvPair, cbAvPair, &cbLen);

		WLog_INFO(TAG, "STR", get_av_pair_string(pair), pair);
		winpr_HexDump(TAG, WLOG_INFO, ntlm_av_pair_get_value_pointer(pAvPair), cbLen);

		pAvPair = ntlm_av_pair_next(pAvPair, &cbAvPair);
	}
}