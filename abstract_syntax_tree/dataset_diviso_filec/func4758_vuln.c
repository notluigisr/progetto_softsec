ConvertTimeZoneAbbrevs(TimeZoneAbbrevTable *tbl,
					   struct tzEntry *abbrevs, int n)
{
	datetkn    *newtbl = tbl->abbrevs;
	int			i;

	tbl->numabbrevs = n;
	for (i = 0; i < n; i++)
	{
		strncpy(newtbl[i].token, abbrevs[i].abbrev, TOKMAXLEN);
		newtbl[i].type = abbrevs[i].is_dst ? DTZ : TZ;
		TOVAL(&newtbl[i], abbrevs[i].offset / MINS_PER_HOUR);
	}

	
	Assert(CheckDateTokenTable("STR", newtbl, n));
}