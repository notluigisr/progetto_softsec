chdlc_print(netdissect_options *ndo, register const u_char *p, u_int length)
{
	u_int proto;

	proto = EXTRACT_16BITS(&p[2]);
	if (ndo->ndo_eflag) {
                ND_PRINT((ndo, "STR",
                       tok2str(chdlc_cast_values, "STR", p[0]),
                       tok2str(ethertype_values, "STR", proto),
                       proto,
                       length));
	}

	length -= CHDLC_HDRLEN;
	p += CHDLC_HDRLEN;

	switch (proto) {
	case ETHERTYPE_IP:
		ip_print(ndo, p, length);
		break;
	case ETHERTYPE_IPV6:
		ip6_print(ndo, p, length);
		break;
	case CHDLC_TYPE_SLARP:
		chdlc_slarp_print(ndo, p, length);
		break;
#if 0
	case CHDLC_TYPE_CDP:
		chdlc_cdp_print(p, length);
		break;
#endif
        case ETHERTYPE_MPLS:
        case ETHERTYPE_MPLS_MULTI:
                mpls_print(ndo, p, length);
		break;
        case ETHERTYPE_ISO:
                
                if (*(p+1) == 0x81 ||
                    *(p+1) == 0x82 ||
                    *(p+1) == 0x83)
                    isoclns_print(ndo, p + 1, length - 1, ndo->ndo_snapend - p - 1);
                else
                    isoclns_print(ndo, p, length, ndo->ndo_snapend - p);
                break;
	default:
                if (!ndo->ndo_eflag)
                        ND_PRINT((ndo, "STR", proto));
                break;
	}

	return (CHDLC_HDRLEN);
}