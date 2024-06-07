stripped_char (gunichar ch)
{
	gunichar decomp[4];
	gunichar retval;
	GUnicodeType utype;
	gsize dlen;

	utype = g_unichar_type (ch);

	switch (utype) {
	case G_UNICODE_CONTROL:
	case G_UNICODE_FORMAT:
	case G_UNICODE_UNASSIGNED:
	case G_UNICODE_SPACING_MARK:
		
		return 0;
	default:
		
		ch = g_unichar_tolower (ch);
		
	case G_UNICODE_LOWERCASE_LETTER:
		if ((dlen = g_unichar_fully_decompose (ch, FALSE, decomp, 4))) {
			retval = decomp[0];
			return retval;
		}
		break;
	}

	return 0;
}