static BOOL ntlm_av_pair_check_data(const NTLM_AV_PAIR* pAvPair, size_t cbAvPair, size_t size)
{
	size_t offset;
	if (!pAvPair || cbAvPair < sizeof(NTLM_AV_PAIR) + size)
		return FALSE;
	if (!ntlm_av_pair_get_next_offset(pAvPair, cbAvPair, &offset))
		return FALSE;
	return cbAvPair >= offset;
}