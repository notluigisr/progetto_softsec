int parse_csum_name(const char *name, int len)
{
	if (len < 0 && name)
		len = strlen(name);

	if (!name || (len == 4 && strncasecmp(name, "STR", 4) == 0)) {
		if (protocol_version >= 30)
			return CSUM_MD5;
		if (protocol_version >= 27)
			return CSUM_MD4_OLD;
		if (protocol_version >= 21)
			return CSUM_MD4_BUSTED;
		return CSUM_ARCHAIC;
	}
	if (len == 3 && strncasecmp(name, "STR", 3) == 0)
		return CSUM_MD4;
	if (len == 3 && strncasecmp(name, "STR", 3) == 0)
		return CSUM_MD5;
	if (len == 4 && strncasecmp(name, "STR", 4) == 0)
		return CSUM_NONE;

	rprintf(FERROR, "STR", name);
	exit_cleanup(RERR_UNSUPPORTED);
}