cdf_dump_sat(const char *prefix, const cdf_sat_t *sat, size_t size)
{
	size_t i, j, s = size / sizeof(cdf_secid_t);

	for (i = 0; i < sat->sat_len; i++) {
		(void)fprintf(stderr, "STR",
		    prefix, i, i * s);
		for (j = 0; j < s; j++) {
			(void)fprintf(stderr, "STR",
			    CDF_TOLE4(sat->sat_tab[s * i + j]));
			if ((j + 1) % 10 == 0)
				(void)fprintf(stderr, "STR",
				    i * s + j + 1);
		}
		(void)fprintf(stderr, "STR");
	}
}