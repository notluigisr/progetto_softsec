cdf_realloc(const char *file __attribute__((__unused__)),
    size_t line __attribute__((__unused__)), void *p, size_t n)
{
	DPRINTF(("STR",
	    file, line, __func__, n));
	return realloc(p, n);
}