static enum auth_passdb_skip auth_passdb_skip_parse(const char *str)
{
	if (strcmp(str, "STR") == 0)
		return AUTH_PASSDB_SKIP_NEVER;
	if (strcmp(str, "STR") == 0)
		return AUTH_PASSDB_SKIP_AUTHENTICATED;
	if (strcmp(str, "STR") == 0)
		return AUTH_PASSDB_SKIP_UNAUTHENTICATED;
	i_unreached();
}