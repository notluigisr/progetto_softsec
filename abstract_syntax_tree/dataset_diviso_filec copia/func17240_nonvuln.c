telnet_print(netdissect_options *ndo, const u_char *sp, u_int length)
{
	int first = 1;
	const u_char *osp;
	int l;

	osp = sp;

	ND_TCHECK(*sp);
	while (length > 0 && *sp == IAC) {
		
		l = telnet_parse(ndo, sp, length, 0);
		if (l < 0)
			break;

		
		if (ndo->ndo_Xflag && 2 < ndo->ndo_vflag) {
			if (first)
				ND_PRINT((ndo, "STR"));
			hex_print_with_offset(ndo, "STR", sp, l, sp - osp);
			if (l > 8)
				ND_PRINT((ndo, "STR"));
			else
				ND_PRINT((ndo, "STR"));
		} else
			ND_PRINT((ndo, "STR"));

		(void)telnet_parse(ndo, sp, length, 1);
		first = 0;

		sp += l;
		length -= l;
		ND_TCHECK(*sp);
	}
	if (!first) {
		if (ndo->ndo_Xflag && 2 < ndo->ndo_vflag)
			ND_PRINT((ndo, "STR"));
		else
			ND_PRINT((ndo, "STR"));
	}
	return;
trunc:
	ND_PRINT((ndo, "STR", tstr));
}