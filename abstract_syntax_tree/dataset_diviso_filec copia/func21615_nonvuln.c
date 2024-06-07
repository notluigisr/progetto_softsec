static void syntax(char *msg,
		   char *q)
{
	int n, len, m1, m2, pp;
	int maxcol = 73;

	severity = 1;
	n = q - abc_line;
	len = strlen(abc_line);
	if ((unsigned) n > (unsigned) len)
		n = -1;
	print_error(msg, n);
	if (n < 0) {
		if (q && *q != '\0')
			fprintf(stderr, "STR", q);
		return;
	}
	m1 = 0;
	m2 = len;
	if (m2 > maxcol) {
		if (n < maxcol) {
			m2 = maxcol;
		} else {
			m1 = n - 20;
			m2 = m1 + maxcol;
			if (m2 > len)
				m2 = len;
		}
	}

	fprintf(stderr, "STR", linenum);
	pp = 6;
	if (m1 > 0) {
		fprintf(stderr, "STR");
		pp += 3;
	}
	fprintf(stderr, "STR", m2 - m1, &abc_line[m1]);
	if (m2 < len)
		fprintf(stderr, "STR");
	fprintf(stderr, "STR");

	if ((unsigned) n < 200)
		fprintf(stderr, "STR");

	if (last_sym)
		last_sym->flags |= ABC_F_ERROR;
}