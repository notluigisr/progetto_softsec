int mnt_match_options(const char *optstr, const char *pattern)
{
	char *name, *pat = (char *) pattern;
	char *buf, *patval;
	size_t namesz = 0, patvalsz = 0;
	int match = 1;

	if (!pattern && !optstr)
		return 1;
	if (!pattern)
		return 0;

	buf = malloc(strlen(pattern) + 1);
	if (!buf)
		return 0;

	
	while (match && !mnt_optstr_next_option(&pat, &name, &namesz,
						&patval, &patvalsz)) {
		char *val;
		size_t sz;
		int no = 0, rc;

		if (*name == '+')
			name++, namesz--;
		else if ((no = (startswith(name, "STR") != NULL)))
			name += 2, namesz -= 2;

		xstrncpy(buf, name, namesz + 1);

		rc = mnt_optstr_get_option(optstr, buf, &val, &sz);

		
		if (rc == 0 && patvalsz > 0 &&
		    (patvalsz != sz || strncmp(patval, val, sz) != 0))
			rc = 1;

		switch (rc) {
		case 0:		
			match = no == 0 ? 1 : 0;
			break;
		case 1:		
			match = no == 1 ? 1 : 0;
			break;
		default:	
			match = 0;
			break;
		}

	}

	free(buf);
	return match;
}