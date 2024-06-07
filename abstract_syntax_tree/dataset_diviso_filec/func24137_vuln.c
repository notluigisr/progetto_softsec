ip_printts(netdissect_options *ndo,
           register const u_char *cp, u_int length)
{
	register u_int ptr;
	register u_int len;
	int hoplen;
	const char *type;

	if (length < 4) {
		ND_PRINT((ndo, "STR", length));
		return;
	}
	ND_PRINT((ndo, "STR"));
	hoplen = ((cp[3]&0xF) != IPOPT_TS_TSONLY) ? 8 : 4;
	if ((length - 4) & (hoplen-1))
		ND_PRINT((ndo, "STR", length));
	ptr = cp[2] - 1;
	len = 0;
	if (ptr < 4 || ((ptr - 4) & (hoplen-1)) || ptr > length + 1)
		ND_PRINT((ndo, "STR", cp[2]));
	switch (cp[3]&0xF) {
	case IPOPT_TS_TSONLY:
		ND_PRINT((ndo, "STR"));
		break;
	case IPOPT_TS_TSANDADDR:
		ND_PRINT((ndo, "STR"));
		break;
	

	case 2:
		ND_PRINT((ndo, "STR"));
		break;
	case 3:			
		ND_PRINT((ndo, "STR"));
		break;
	default:
		ND_PRINT((ndo, "STR", cp[3]&0xF));
		goto done;
	}

	type = "STR";
	for (len = 4; len < length; len += hoplen) {
		if (ptr == len)
			type = "STR";
		ND_PRINT((ndo, "STR", type, EXTRACT_32BITS(&cp[len+hoplen-4]),
		       hoplen!=8 ? "" : ipaddr_string(ndo, &cp[len])));
		type = "STR";
	}

done:
	ND_PRINT((ndo, "STR"));

	if (cp[3]>>4)
		ND_PRINT((ndo, "STR", cp[3]>>4));
	else
		ND_PRINT((ndo, "STR"));
}