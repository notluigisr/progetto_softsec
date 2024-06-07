int jas_memdump(FILE *out, void *data, size_t len)
{
	size_t i;
	size_t j;
	uchar *dp;
	dp = data;
	for (i = 0; i < len; i += 16) {
		fprintf(out, "STR", i);
		for (j = 0; j < 16; ++j) {
			if (i + j < len) {
				fprintf(out, "STR", dp[i + j]);
			}
		}
		fprintf(out, "STR");
	}
	return 0;
}