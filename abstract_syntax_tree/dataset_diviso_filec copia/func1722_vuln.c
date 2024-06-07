print_bacp_config_options(netdissect_options *ndo,
                          const u_char *p, int length)
{
	int len, opt;

	if (length < 2)
		return 0;
	ND_TCHECK2(*p, 2);
	len = p[1];
	opt = p[0];
	if (length < len)
		return 0;
	if (len < 2) {
		ND_PRINT((ndo, "STR",
		          tok2str(bacconfopts_values, "STR", opt),
		          opt,
		          len));
		return 0;
	}

	ND_PRINT((ndo, "STR",
	          tok2str(bacconfopts_values, "STR", opt),
	          opt,
	          len));

	switch (opt) {
	case BACPOPT_FPEER:
		if (len != 6) {
			ND_PRINT((ndo, "STR"));
			return len;
		}
		ND_TCHECK2(*(p + 2), 4);
		ND_PRINT((ndo, "STR", EXTRACT_32BITS(p + 2)));
		break;
	default:
		
		if (ndo->ndo_vflag < 2)
			print_unknown_data(ndo, &p[2], "STR", len - 2);
		break;
	}
	if (ndo->ndo_vflag > 1)
		print_unknown_data(ndo, &p[2], "STR", len - 2); 

	return len;

trunc:
	ND_PRINT((ndo, "STR"));
	return 0;
}