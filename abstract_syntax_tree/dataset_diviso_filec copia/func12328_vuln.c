ip_printroute(netdissect_options *ndo,
              register const u_char *cp, u_int length)
{
	register u_int ptr;
	register u_int len;

	if (length < 3) {
		ND_PRINT((ndo, "STR", length));
		return;
	}
	if ((length + 1) & 3)
		ND_PRINT((ndo, "STR", length));
	ptr = cp[2] - 1;
	if (ptr < 3 || ((ptr + 1) & 3) || ptr > length + 1)
		ND_PRINT((ndo, "STR", cp[2]));

	for (len = 3; len < length; len += 4) {
		ND_PRINT((ndo, "STR", ipaddr_string(ndo, &cp[len])));
		if (ptr > len)
			ND_PRINT((ndo, "STR"));
	}
}