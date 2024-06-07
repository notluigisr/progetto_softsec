mobility_opt_print(netdissect_options *ndo,
                   const u_char *bp, const unsigned len)
{
	unsigned i, optlen;

	for (i = 0; i < len; i += optlen) {
		ND_TCHECK(bp[i]);
		if (bp[i] == IP6MOPT_PAD1)
			optlen = 1;
		else {
			if (i + 1 < len) {
				ND_TCHECK(bp[i + 1]);
				optlen = bp[i + 1] + 2;
			}
			else
				goto trunc;
		}
		if (i + optlen > len)
			goto trunc;
		ND_TCHECK(bp[i + optlen]);

		switch (bp[i]) {
		case IP6MOPT_PAD1:
			ND_PRINT((ndo, "STR"));
			break;
		case IP6MOPT_PADN:
			if (len - i < IP6MOPT_MINLEN) {
				ND_PRINT((ndo, "STR"));
				goto trunc;
			}
			ND_PRINT((ndo, "STR"));
			break;
		case IP6MOPT_REFRESH:
			if (len - i < IP6MOPT_REFRESH_MINLEN) {
				ND_PRINT((ndo, "STR"));
				goto trunc;
			}
			
			ND_PRINT((ndo, "STR",
				EXTRACT_16BITS(&bp[i+2]) << 2));
			break;
		case IP6MOPT_ALTCOA:
			if (len - i < IP6MOPT_ALTCOA_MINLEN) {
				ND_PRINT((ndo, "STR"));
				goto trunc;
			}
			ND_PRINT((ndo, "STR", ip6addr_string(ndo, &bp[i+2])));
			break;
		case IP6MOPT_NONCEID:
			if (len - i < IP6MOPT_NONCEID_MINLEN) {
				ND_PRINT((ndo, "STR"));
				goto trunc;
			}
			ND_PRINT((ndo, "STR",
				EXTRACT_16BITS(&bp[i+2]),
				EXTRACT_16BITS(&bp[i+4])));
			break;
		case IP6MOPT_AUTH:
			if (len - i < IP6MOPT_AUTH_MINLEN) {
				ND_PRINT((ndo, "STR"));
				goto trunc;
			}
			ND_PRINT((ndo, "STR"));
			break;
		default:
			if (len - i < IP6MOPT_MINLEN) {
				ND_PRINT((ndo, "STR", bp[i]));
				goto trunc;
			}
			ND_PRINT((ndo, "STR", bp[i], bp[i + 1]));
			break;
		}
	}
	return 0;

trunc:
	return 1;
}