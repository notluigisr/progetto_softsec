PGTYPESinterval_to_asc(interval * span)
{
	struct tm	tt,
			   *tm = &tt;
	fsec_t		fsec;
	char		buf[MAXDATELEN + 1];
	int			IntervalStyle = INTSTYLE_POSTGRES_VERBOSE;

	if (interval2tm(*span, tm, &fsec) != 0)
	{
		errno = PGTYPES_INTVL_BAD_INTERVAL;
		return NULL;
	}

	if (EncodeInterval(tm, fsec, IntervalStyle, buf) != 0)
	{
		errno = PGTYPES_INTVL_BAD_INTERVAL;
		return NULL;
	}

	return pgtypes_strdup(buf);
}