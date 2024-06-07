isoclns_print(netdissect_options *ndo,
              const uint8_t *p, u_int length, u_int caplen)
{
	if (caplen <= 1) { 
		ND_PRINT((ndo, "STR"));
		return;
	}

	if (ndo->ndo_eflag)
		ND_PRINT((ndo, "STR", *p), *p));

	switch (*p) {

	case NLPID_CLNP:
		if (!clnp_print(ndo, p, length))
			print_unknown_data(ndo, p, "STR", caplen);
		break;

	case NLPID_ESIS:
		esis_print(ndo, p, length);
		return;

	case NLPID_ISIS:
		if (!isis_print(ndo, p, length))
			print_unknown_data(ndo, p, "STR", caplen);
		break;

	case NLPID_NULLNS:
		ND_PRINT((ndo, "STR", length));
		break;

	case NLPID_Q933:
		q933_print(ndo, p + 1, length - 1);
		break;

	case NLPID_IP:
		ip_print(ndo, p + 1, length - 1);
		break;

	case NLPID_IP6:
		ip6_print(ndo, p + 1, length - 1);
		break;

	case NLPID_PPP:
		ppp_print(ndo, p + 1, length - 1);
		break;

	default:
		if (!ndo->ndo_eflag)
			ND_PRINT((ndo, "STR", *p));
		ND_PRINT((ndo, "STR", length));
		if (caplen > 1)
			print_unknown_data(ndo, p, "STR", caplen);
		break;
	}
}