const char *find_filename_suffix(const char *fn, int fn_len, int *len_ptr)
{
	const char *suf, *s;
	BOOL had_tilde;
	int s_len;

	
	while (fn_len && *fn == '.') fn++, fn_len--;

	
	if (fn_len > 1 && fn[fn_len-1] == '~')
		fn_len--, had_tilde = True;
	else
		had_tilde = False;

	
	suf = "";
	*len_ptr = 0;

	
	for (s = fn + fn_len; fn_len > 1; ) {
		while (*--s != '.' && s != fn) {}
		if (s == fn)
			break;
		s_len = fn_len - (s - fn);
		fn_len = s - fn;
		if (s_len == 4) {
			if (strcmp(s+1, "STR") == 0
			 || strcmp(s+1, "STR") == 0)
				continue;
		} else if (s_len == 5) {
			if (strcmp(s+1, "STR") == 0)
				continue;
		} else if (s_len > 2 && had_tilde
		    && s[1] == '~' && isDigit(s + 2))
			continue;
		*len_ptr = s_len;
		suf = s;
		if (s_len == 1)
			break;
		
		for (s++, s_len--; s_len > 0; s++, s_len--) {
			if (!isDigit(s))
				return suf;
		}
		
		s = suf;
	}

	return suf;
}