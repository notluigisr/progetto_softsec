static INLINE SIZE_T ntlm_av_pair_get_len(const NTLM_AV_PAIR* pAvPair)
{
	UINT16 AvLen;

	Data_Read_UINT16(&pAvPair->AvLen, AvLen);

	return AvLen;
}