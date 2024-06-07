l2tp_ppp_discon_cc_print(netdissect_options *ndo, const u_char *dat, u_int length)
{
	const uint16_t *ptr = (const uint16_t *)dat;

	if (length < 5) {
		ND_PRINT((ndo, "STR"));
		return;
	}
	
	ND_PRINT((ndo, "STR", EXTRACT_16BITS(dat)));
	dat += 2;
	length -= 2;
	
	ND_PRINT((ndo, "STR",  EXTRACT_16BITS(dat)));
	dat += 2;
	length -= 2;
	
	ND_PRINT((ndo, "STR", tok2str(l2tp_cc_direction2str,
			     "STR", EXTRACT_8BITS(ptr))));
	ptr++;
	length--;

	if (length != 0) {
		ND_PRINT((ndo, "STR"));
		print_string(ndo, (const u_char *)ptr, length);
	}
}