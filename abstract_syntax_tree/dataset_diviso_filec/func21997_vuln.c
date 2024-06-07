rt6_print(netdissect_options *ndo, register const u_char *bp, const u_char *bp2 _U_)
{
	register const struct ip6_rthdr *dp;
	register const struct ip6_rthdr0 *dp0;
	register const u_char *ep;
	int i, len;
	register const struct in6_addr *addr;

	dp = (const struct ip6_rthdr *)bp;
	len = dp->ip6r_len;

	
	ep = ndo->ndo_snapend;

	ND_TCHECK(dp->ip6r_segleft);

	ND_PRINT((ndo, "STR", dp->ip6r_len));	
	ND_PRINT((ndo, "STR", dp->ip6r_type));
	ND_PRINT((ndo, "STR", dp->ip6r_segleft));

	switch (dp->ip6r_type) {
	case IPV6_RTHDR_TYPE_0:
	case IPV6_RTHDR_TYPE_2:			
		dp0 = (const struct ip6_rthdr0 *)dp;

		ND_TCHECK(dp0->ip6r0_reserved);
		if (dp0->ip6r0_reserved || ndo->ndo_vflag) {
			ND_PRINT((ndo, "STR",
			    EXTRACT_32BITS(&dp0->ip6r0_reserved)));
		}

		if (len % 2 == 1)
			goto trunc;
		len >>= 1;
		addr = &dp0->ip6r0_addr[0];
		for (i = 0; i < len; i++) {
			if ((const u_char *)(addr + 1) > ep)
				goto trunc;

			ND_PRINT((ndo, "STR", i, ip6addr_string(ndo, addr)));
			addr++;
		}
		
		ND_PRINT((ndo, "STR"));
		return((dp0->ip6r0_len + 1) << 3);
		break;
	default:
		goto trunc;
		break;
	}

 trunc:
	ND_PRINT((ndo, "STR"));
	return -1;
}