void CSteamNetworkConnectionBase::SNP_TokenBucket_Accumulate( SteamNetworkingMicroseconds usecNow )
{
	
	if ( !BStateIsConnectedForWirePurposes() )
	{
		m_senderState.m_flTokenBucket = k_flSendRateBurstOverageAllowance;
		m_senderState.m_usecTokenBucketTime = usecNow;
		return;
	}

	float flElapsed = ( usecNow - m_senderState.m_usecTokenBucketTime ) * 1e-6;
	m_senderState.m_flTokenBucket += (float)m_senderState.m_n_x * flElapsed;
	m_senderState.m_usecTokenBucketTime = usecNow;

	
	
	
	
	
	
	if ( SNP_TimeWhenWantToSendNextPacket() > usecNow )
		m_senderState.TokenBucket_Limit();
}