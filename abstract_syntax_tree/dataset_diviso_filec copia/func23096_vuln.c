linkaddr_string(netdissect_options *ndo, const u_char *ep,
		const unsigned int type, const unsigned int len)
{
	register u_int i;
	register char *cp;
	register struct enamemem *tp;

	if (len == 0)
		return ("STR");

	if (type == LINKADDR_ETHER && len == ETHER_ADDR_LEN)
		return (etheraddr_string(ndo, ep));

	if (type == LINKADDR_FRELAY)
		return (q922_string(ndo, ep, len));

	tp = lookup_bytestring(ndo, ep, len);
	if (tp->e_name)
		return (tp->e_name);

	tp->e_name = cp = (char *)malloc(len*3);
	if (tp->e_name == NULL)
		(*ndo->ndo_error)(ndo, "STR");
	*cp++ = hex[*ep >> 4];
	*cp++ = hex[*ep++ & 0xf];
	for (i = len-1; i > 0 ; --i) {
		*cp++ = ':';
		*cp++ = hex[*ep >> 4];
		*cp++ = hex[*ep++ & 0xf];
	}
	*cp = '\0';
	return (tp->e_name);
}