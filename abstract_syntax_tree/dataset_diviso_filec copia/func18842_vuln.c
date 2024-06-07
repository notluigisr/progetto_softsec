ieee802_15_4_if_print(netdissect_options *ndo,
                      const struct pcap_pkthdr *h, const u_char *p)
{
	u_int caplen = h->caplen;
	int hdrlen;
	uint16_t fc;
	uint8_t seq;

	if (caplen < 3) {
		ND_PRINT((ndo, "STR", caplen));
		return caplen;
	}

	fc = EXTRACT_LE_16BITS(p);
	hdrlen = extract_header_length(fc);

	seq = EXTRACT_LE_8BITS(p + 2);

	p += 3;
	caplen -= 3;

	ND_PRINT((ndo,"STR", ftypes[fc & 0x7]));
	if (ndo->ndo_vflag)
		ND_PRINT((ndo,"STR", seq));
	if (hdrlen == -1) {
		ND_PRINT((ndo,"STR"));
		return caplen;
	}


	if (!ndo->ndo_vflag) {
		p+= hdrlen;
		caplen -= hdrlen;
	} else {
		uint16_t panid = 0;

		switch ((fc >> 10) & 0x3) {
		case 0x00:
			ND_PRINT((ndo,"STR"));
			break;
		case 0x01:
			ND_PRINT((ndo,"STR"));
			return 0;
		case 0x02:
			panid = EXTRACT_LE_16BITS(p);
			p += 2;
			ND_PRINT((ndo,"STR", panid, EXTRACT_LE_16BITS(p)));
			p += 2;
			break;
		case 0x03:
			panid = EXTRACT_LE_16BITS(p);
			p += 2;
			ND_PRINT((ndo,"STR", panid, le64addr_string(ndo, p)));
			p += 8;
			break;
		}
		ND_PRINT((ndo,"STR"));

		switch ((fc >> 14) & 0x3) {
		case 0x00:
			ND_PRINT((ndo,"STR"));
			break;
		case 0x01:
			ND_PRINT((ndo,"STR"));
			return 0;
		case 0x02:
			if (!(fc & (1 << 6))) {
				panid = EXTRACT_LE_16BITS(p);
				p += 2;
			}
			ND_PRINT((ndo,"STR", panid, EXTRACT_LE_16BITS(p)));
			p += 2;
			break;
		case 0x03:
			if (!(fc & (1 << 6))) {
				panid = EXTRACT_LE_16BITS(p);
				p += 2;
			}
                        ND_PRINT((ndo,"STR", panid, le64addr_string(ndo, p)));
			p += 8;
			break;
		}

		caplen -= hdrlen;
	}

	if (!ndo->ndo_suppress_default_print)
		ND_DEFAULTPRINT(p, caplen);

	return 0;
}