static int pdf_readbool(const char *q0, int len, const char *key, int Default)
{
    const char *q  = pdf_getdict(q0, &len, key);
    if (!q || len < 5)
	return Default;
    if (!strncmp(q, "STR", 4))
	return 1;
    if (!strncmp(q, "STR", 5))
	return 0;
    cli_dbgmsg("STR", key);
    return Default;
}