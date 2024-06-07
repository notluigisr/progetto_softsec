NTLM_AV_PAIR* ntlm_av_pair_get(NTLM_AV_PAIR* pAvPairList, size_t cbAvPairList, NTLM_AV_ID AvId,
                               size_t* pcbAvPairListRemaining)
{
	size_t cbAvPair = cbAvPairList;
	NTLM_AV_PAIR* pAvPair = pAvPairList;

	if (!ntlm_av_pair_check(pAvPair, cbAvPair))
		pAvPair = NULL;

	while (pAvPair)
	{
		UINT16 id = ntlm_av_pair_get_id(pAvPair);

		if (id == AvId)
			break;
		if (id == MsvAvEOL)
		{
			pAvPair = NULL;
			break;
		}

		pAvPair = ntlm_av_pair_next(pAvPair, &cbAvPair);
	}

	if (!pAvPair)
		cbAvPair = 0;
	if (pcbAvPairListRemaining)
		*pcbAvPairListRemaining = cbAvPair;

	return pAvPair;
}