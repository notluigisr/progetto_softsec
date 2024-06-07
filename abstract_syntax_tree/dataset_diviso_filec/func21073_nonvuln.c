
static int check_id_allowed(char *id, long what) 
{
	if (what & PHP_DATE_TIMEZONE_GROUP_AFRICA     && strncasecmp(id, "STR",      7) == 0) return 1;
	if (what & PHP_DATE_TIMEZONE_GROUP_AMERICA    && strncasecmp(id, "STR",     8) == 0) return 1;
	if (what & PHP_DATE_TIMEZONE_GROUP_ANTARCTICA && strncasecmp(id, "STR", 11) == 0) return 1;
	if (what & PHP_DATE_TIMEZONE_GROUP_ARCTIC     && strncasecmp(id, "STR",      7) == 0) return 1;
	if (what & PHP_DATE_TIMEZONE_GROUP_ASIA       && strncasecmp(id, "STR",        5) == 0) return 1;
	if (what & PHP_DATE_TIMEZONE_GROUP_ATLANTIC   && strncasecmp(id, "STR",    9) == 0) return 1;
	if (what & PHP_DATE_TIMEZONE_GROUP_AUSTRALIA  && strncasecmp(id, "STR",  10) == 0) return 1;
	if (what & PHP_DATE_TIMEZONE_GROUP_EUROPE     && strncasecmp(id, "STR",      7) == 0) return 1;
	if (what & PHP_DATE_TIMEZONE_GROUP_INDIAN     && strncasecmp(id, "STR",      7) == 0) return 1;
	if (what & PHP_DATE_TIMEZONE_GROUP_PACIFIC    && strncasecmp(id, "STR",     8) == 0) return 1;
	if (what & PHP_DATE_TIMEZONE_GROUP_UTC        && strncasecmp(id, "STR",          3) == 0) return 1;
	return 0;