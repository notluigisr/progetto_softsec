EUnsignedCert CSteamNetworkConnectionUDP::AllowRemoteUnsignedCert()
{
	
	
	
	
	
	

	
	int nAllow = m_connectionConfig.m_IP_AllowWithoutAuth.Get();
	if ( nAllow > 1 )
		return k_EUnsignedCert_Allow;
	if ( nAllow == 1 )
		return k_EUnsignedCert_AllowWarn;

	
	return k_EUnsignedCert_Disallow;
}