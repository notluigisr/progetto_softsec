bgp_open_print(netdissect_options *ndo,
               const u_char *dat, int length)
{
	struct bgp_open bgpo;
	struct bgp_opt bgpopt;
	const u_char *opt;
	int i;

	ND_TCHECK2(dat[0], BGP_OPEN_SIZE);
	memcpy(&bgpo, dat, BGP_OPEN_SIZE);

	ND_PRINT((ndo, "STR", bgpo.bgpo_version));
	ND_PRINT((ndo, "STR",
	    as_printf(ndo, astostr, sizeof(astostr), ntohs(bgpo.bgpo_myas))));
	ND_PRINT((ndo, "STR", ntohs(bgpo.bgpo_holdtime)));
	ND_PRINT((ndo, "STR", ipaddr_string(ndo, &bgpo.bgpo_id)));
	ND_PRINT((ndo, "STR", bgpo.bgpo_optlen));

        
        if (length < bgpo.bgpo_optlen+BGP_OPEN_SIZE)
            return;

	
	opt = &((const struct bgp_open *)dat)->bgpo_optlen;
	opt++;

	i = 0;
	while (i < bgpo.bgpo_optlen) {
		ND_TCHECK2(opt[i], BGP_OPT_SIZE);
		memcpy(&bgpopt, &opt[i], BGP_OPT_SIZE);
		if (i + 2 + bgpopt.bgpopt_len > bgpo.bgpo_optlen) {
			ND_PRINT((ndo, "STR", bgpopt.bgpopt_type, bgpopt.bgpopt_len));
			break;
		}

		ND_PRINT((ndo, "STR",
		       tok2str(bgp_opt_values,"STR",
				  bgpopt.bgpopt_type),
		       bgpopt.bgpopt_type,
		       bgpopt.bgpopt_len));

		
		switch(bgpopt.bgpopt_type) {

		case BGP_OPT_CAP:
			bgp_capabilities_print(ndo, &opt[i+BGP_OPT_SIZE],
			    bgpopt.bgpopt_len);
			break;

		case BGP_OPT_AUTH:
		default:
		       ND_PRINT((ndo, "STR",
			   bgpopt.bgpopt_type));
		       break;
		}
		i += BGP_OPT_SIZE + bgpopt.bgpopt_len;
	}
	return;
trunc:
	ND_PRINT((ndo, "STR", tstr));
}