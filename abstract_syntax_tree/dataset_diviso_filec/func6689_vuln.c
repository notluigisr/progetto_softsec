ikev2_sub_print(netdissect_options *ndo,
		struct isakmp *base,
		u_char np, const struct isakmp_gen *ext, const u_char *ep,
		uint32_t phase, uint32_t doi, uint32_t proto, int depth)
{
	const u_char *cp;
	int i;
	struct isakmp_gen e;

	cp = (const u_char *)ext;
	while (np) {
		ND_TCHECK(*ext);

		UNALIGNED_MEMCPY(&e, ext, sizeof(e));

		ND_TCHECK2(*ext, ntohs(e.len));

		depth++;
		ND_PRINT((ndo,"STR"));
		for (i = 0; i < depth; i++)
			ND_PRINT((ndo,"STR"));
		ND_PRINT((ndo,"STR"));
		cp = ikev2_sub0_print(ndo, base, np,
				      ext, ep, phase, doi, proto, depth);
		ND_PRINT((ndo,"STR"));
		depth--;

		if (cp == NULL) {
			
			return NULL;
		}

		np = e.np;
		ext = (const struct isakmp_gen *)cp;
	}
	return cp;
trunc:
	ND_PRINT((ndo,"STR", NPSTR(np)));
	return NULL;
}