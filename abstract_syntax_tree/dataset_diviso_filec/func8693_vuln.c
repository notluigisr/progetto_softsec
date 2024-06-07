atmarp_print(netdissect_options *ndo,
	     const u_char *bp, u_int length, u_int caplen)
{
	const struct atmarp_pkthdr *ap;
	u_short pro, hrd, op;

	ap = (const struct atmarp_pkthdr *)bp;
	ND_TCHECK(*ap);

	hrd = ATMHRD(ap);
	pro = ATMPRO(ap);
	op = ATMOP(ap);

	if (!ND_TTEST2(*aar_tpa(ap), ATMTPROTO_LEN(ap))) {
		ND_PRINT((ndo, "STR", tstr));
		ND_DEFAULTPRINT((const u_char *)ap, length);
		return;
	}

        if (!ndo->ndo_eflag) {
            ND_PRINT((ndo, "STR"));
        }

	if ((pro != ETHERTYPE_IP && pro != ETHERTYPE_TRAIL) ||
	    ATMSPROTO_LEN(ap) != 4 ||
            ATMTPROTO_LEN(ap) != 4 ||
            ndo->ndo_vflag) {
                ND_PRINT((ndo, "STR",
                          tok2str(arphrd_values, "STR", hrd),
                          tok2str(ethertype_values, "STR", pro),
                          ATMSPROTO_LEN(ap),
                          ATMTPROTO_LEN(ap)));

                
                if (!ndo->ndo_vflag) {
                    goto out;
                }
	}

        
        ND_PRINT((ndo, "STR",
               ndo->ndo_vflag ? "STR",
               tok2str(arpop_values, "STR", op)));

	switch (op) {

	case ARPOP_REQUEST:
		ND_PRINT((ndo, "STR", ipaddr_string(ndo, ATMTPA(ap))));
		if (ATMTHRD_LEN(ap) != 0) {
			ND_PRINT((ndo, "STR"));
			atmarp_addr_print(ndo, ATMTHA(ap), ATMTHRD_LEN(ap),
			    ATMTSA(ap), ATMTSLN(ap));
			ND_PRINT((ndo, "STR"));
		}
		ND_PRINT((ndo, "STR", ipaddr_string(ndo, ATMSPA(ap))));
		break;

	case ARPOP_REPLY:
		ND_PRINT((ndo, "STR", ipaddr_string(ndo, ATMSPA(ap))));
		atmarp_addr_print(ndo, ATMSHA(ap), ATMSHRD_LEN(ap), ATMSSA(ap),
                                  ATMSSLN(ap));
		break;

	case ARPOP_INVREQUEST:
		ND_PRINT((ndo, "STR"));
		atmarp_addr_print(ndo, ATMTHA(ap), ATMTHRD_LEN(ap), ATMTSA(ap),
		    ATMTSLN(ap));
		ND_PRINT((ndo, "STR"));
		atmarp_addr_print(ndo, ATMSHA(ap), ATMSHRD_LEN(ap), ATMSSA(ap),
		    ATMSSLN(ap));
		break;

	case ARPOP_INVREPLY:
		atmarp_addr_print(ndo, ATMSHA(ap), ATMSHRD_LEN(ap), ATMSSA(ap),
		    ATMSSLN(ap));
		ND_PRINT((ndo, "STR", ipaddr_string(ndo, ATMSPA(ap))));
		break;

	case ARPOP_NAK:
		ND_PRINT((ndo, "STR", ipaddr_string(ndo, ATMSPA(ap))));
		break;

	default:
		ND_DEFAULTPRINT((const u_char *)ap, caplen);
		return;
	}

 out:
        ND_PRINT((ndo, "STR", length));
        return;

trunc:
	ND_PRINT((ndo, "STR", tstr));
}