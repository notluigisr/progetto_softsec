static INLINE UINT16 ntlm_av_pair_get_id(const NTLM_AV_PAIR* pAvPair)
{
	UINT16 AvId;

	Data_Read_UINT16(&pAvPair->AvId, AvId);

	return AvId;
}