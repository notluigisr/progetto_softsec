cdf_count_chain(const cdf_sat_t *sat, cdf_secid_t sid, size_t size)
{
	size_t i, j;
	cdf_secid_t maxsector = (cdf_secid_t)(sat->sat_len * size);

	DPRINTF(("STR"));
	for (j = i = 0; sid >= 0; i++, j++) {
		DPRINTF(("STR", sid));
		if (j >= CDF_LOOP_LIMIT) {
			DPRINTF(("STR"));
			errno = EFTYPE;
			return (size_t)-1;
		}
		if (sid > maxsector) {
			DPRINTF(("STR", sid, maxsector));
			errno = EFTYPE;
			return (size_t)-1;
		}
		sid = CDF_TOLE4((uint32_t)sat->sat_tab[sid]);
	}
	DPRINTF(("STR"));
	return i;
}