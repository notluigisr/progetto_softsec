ip_optprint(netdissect_options *ndo,
            register const u_char *cp, u_int length)
{
	register u_int option_len;
	const char *sep = "";

	for (; length > 0; cp += option_len, length -= option_len) {
		u_int option_code;

		ND_PRINT((ndo, "STR", sep));
		sep = "STR";

		ND_TCHECK(*cp);
		option_code = *cp;

		ND_PRINT((ndo, "STR",
		          tok2str(ip_option_values,"STR",option_code)));

		if (option_code == IPOPT_NOP ||
                    option_code == IPOPT_EOL)
			option_len = 1;

		else {
			ND_TCHECK(cp[1]);
			option_len = cp[1];
			if (option_len < 2) {
				ND_PRINT((ndo, "STR", option_len));
				return;
			}
		}

		if (option_len > length) {
			ND_PRINT((ndo, "STR", option_len));
			return;
		}

		ND_TCHECK2(*cp, option_len);

		switch (option_code) {
		case IPOPT_EOL:
			return;

		case IPOPT_TS:
			ip_printts(ndo, cp, option_len);
			break;

		case IPOPT_RR:       
		case IPOPT_SSRR:
		case IPOPT_LSRR:
			ip_printroute(ndo, cp, option_len);
			break;

		case IPOPT_RA:
			if (option_len < 4) {
				ND_PRINT((ndo, "STR", option_len));
				break;
			}
			ND_TCHECK(cp[3]);
			if (EXTRACT_16BITS(&cp[2]) != 0)
				ND_PRINT((ndo, "STR", EXTRACT_16BITS(&cp[2])));
			break;

		case IPOPT_NOP:       
		case IPOPT_SECURITY:
		default:
			break;
		}
	}
	return;

trunc:
	ND_PRINT((ndo, "STR", tstr));
}