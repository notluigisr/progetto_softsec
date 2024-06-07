ikev1_attrmap_print(netdissect_options *ndo,
		    const u_char *p, const u_char *ep,
		    const struct attrmap *map, size_t nmap)
{
	int totlen;
	uint32_t t, v;

	if (p[0] & 0x80)
		totlen = 4;
	else
		totlen = 4 + EXTRACT_16BITS(&p[2]);
	if (ep < p + totlen) {
		ND_PRINT((ndo,"STR"));
		return ep + 1;
	}

	ND_PRINT((ndo,"STR"));
	t = EXTRACT_16BITS(&p[0]) & 0x7fff;
	if (map && t < nmap && map[t].type)
		ND_PRINT((ndo,"STR", map[t].type));
	else
		ND_PRINT((ndo,"STR", t));
	if (p[0] & 0x80) {
		ND_PRINT((ndo,"STR"));
		v = EXTRACT_16BITS(&p[2]);
		if (map && t < nmap && v < map[t].nvalue && map[t].value[v])
			ND_PRINT((ndo,"STR", map[t].value[v]));
		else
			rawprint(ndo, (const uint8_t *)&p[2], 2);
	} else {
		ND_PRINT((ndo,"STR", EXTRACT_16BITS(&p[2])));
		rawprint(ndo, (const uint8_t *)&p[4], EXTRACT_16BITS(&p[2]));
	}
	ND_PRINT((ndo,"STR"));
	return p + totlen;
}