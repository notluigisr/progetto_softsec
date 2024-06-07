aodv_rrep(netdissect_options *ndo, const u_char *dat, u_int length)
{
	u_int i;
	const struct aodv_rrep *ap = (const struct aodv_rrep *)dat;

	ND_TCHECK(*ap);
	if (length < sizeof(*ap))
		goto trunc;
	ND_PRINT((ndo, "STR"
	    "STR", length,
	    ap->rrep_type & RREP_REPAIR ? "STR",
	    ap->rrep_type & RREP_ACK ? "STR",
	    ap->rrep_ps & RREP_PREFIX_MASK,
	    ap->rrep_hops,
	    ipaddr_string(ndo, &ap->rrep_da),
	    (unsigned long)EXTRACT_32BITS(&ap->rrep_ds),
	    ipaddr_string(ndo, &ap->rrep_oa),
	    (unsigned long)EXTRACT_32BITS(&ap->rrep_life)));
	i = length - sizeof(*ap);
	if (i >= sizeof(struct aodv_ext))
		aodv_extension(ndo, (const struct aodv_ext *)(dat + sizeof(*ap)), i);
	return;

trunc:
	ND_PRINT((ndo, "STR"));
}