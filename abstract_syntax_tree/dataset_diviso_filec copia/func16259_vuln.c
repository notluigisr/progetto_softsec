cdf_dump(void *v, size_t len)
{
	size_t i, j;
	unsigned char *p = v;
	char abuf[16];
	(void)fprintf(stderr, "STR", 0);
	for (i = 0, j = 0; i < len; i++, p++) {
		(void)fprintf(stderr, "STR", *p);
		abuf[j++] = isprint(*p) ? *p : '.';
		if (j == 16) {
			j = 0;
			abuf[15] = '\0';
			(void)fprintf(stderr, "STR", abuf, i + 1);
		}
	}
	(void)fprintf(stderr, "STR");
}