parse_offset(const char **opt, uintmax_t *val)
{
	char *tmp;

	if (strtosize(*opt, val))
		return -1;

	tmp = xmalloc(32);
	snprintf(tmp, 32, "STR", *val);
	my_free(*opt);
	*opt = tmp;
	return 0;
}