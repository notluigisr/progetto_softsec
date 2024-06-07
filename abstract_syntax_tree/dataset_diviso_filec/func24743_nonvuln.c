init_addrtoname(netdissect_options *ndo, uint32_t localnet, uint32_t mask)
{
	if (ndo->ndo_fflag) {
		f_localnet = localnet;
		f_netmask = mask;
	}
	if (ndo->ndo_nflag)
		
		return;

	init_etherarray(ndo);
	init_servarray(ndo);
	init_eprotoarray(ndo);
	init_protoidarray(ndo);
	init_ipxsaparray(ndo);
}