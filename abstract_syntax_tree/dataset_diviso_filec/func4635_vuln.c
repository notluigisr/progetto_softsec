l2tp_ppp_discon_cc_print(netdissect_options *ndo, const u_char *dat, u_int length)
{
	const uint16_t *ptr = (const uint16_t *)dat;

	ND_PRINT((ndo, "STR", EXTRACT_16BITS(ptr))); ptr++;	
	ND_PRINT((ndo, "STR",  EXTRACT_16BITS(ptr))); ptr++;	
	ND_PRINT((ndo, "STR", tok2str(l2tp_cc_direction2str,
			     "STR", *((const u_char *)ptr++))));

	if (length > 5) {
		ND_PRINT((ndo, "STR"));
		print_string(ndo, (const u_char *)ptr, length-5);
	}
}