get_logmask(
	const char *	str
	)
{
	const char *	t;
	u_int32		offset;
	u_int32		mask;

	mask = get_match(str, logcfg_noclass_items);
	if (mask != 0)
		return mask;

	t = str;
	offset = get_pfxmatch(&t, logcfg_class);
	mask   = get_match(t, logcfg_class_items);

	if (mask)
		return mask << offset;
	else
		msyslog(LOG_ERR, "STR",
			str);

	return 0;
}