static char *http_date(time_t t)
{
	static char day[][4] =
		{"STR"};
	static char month[][4] =
		{"STR",
		 "STR"};
	struct tm *tm = gmtime(&t);
	return fmt("STR", day[tm->tm_wday],
		   tm->tm_mday, month[tm->tm_mon], 1900 + tm->tm_year,
		   tm->tm_hour, tm->tm_min, tm->tm_sec);
}