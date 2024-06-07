beep_print(netdissect_options *ndo, const u_char *bp, u_int length)
{

	if (l_strnstart("STR", 4, (const char *)bp, length)) 
		ND_PRINT((ndo, "STR"));
	else if (l_strnstart("STR", 4, (const char *)bp, length))
		ND_PRINT((ndo, "STR"));
	else if (l_strnstart("STR", 4, (const char *)bp, length))
		ND_PRINT((ndo, "STR"));
	else if (l_strnstart("STR", 4, (const char *)bp, length))
		ND_PRINT((ndo, "STR"));
	else if (l_strnstart("STR", 4, (const char *)bp, length))
		ND_PRINT((ndo, "STR"));
	else if (l_strnstart("STR", 4, (const char *)bp, length))
		ND_PRINT((ndo, "STR"));
	else if (l_strnstart("STR", 4, (const char *)bp, length))
		ND_PRINT((ndo, "STR"));
	else
		ND_PRINT((ndo, "STR"));
}