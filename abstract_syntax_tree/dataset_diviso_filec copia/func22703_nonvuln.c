DecodeTimezone(char *str, int *tzp)
{
	int			tz;
	int			hr,
				min,
				sec = 0;
	char	   *cp;

	
	if (*str != '+' && *str != '-')
		return DTERR_BAD_FORMAT;

	errno = 0;
	hr = strtoi(str + 1, &cp, 10);
	if (errno == ERANGE)
		return DTERR_TZDISP_OVERFLOW;

	
	if (*cp == ':')
	{
		errno = 0;
		min = strtoi(cp + 1, &cp, 10);
		if (errno == ERANGE)
			return DTERR_TZDISP_OVERFLOW;
		if (*cp == ':')
		{
			errno = 0;
			sec = strtoi(cp + 1, &cp, 10);
			if (errno == ERANGE)
				return DTERR_TZDISP_OVERFLOW;
		}
	}
	
	else if (*cp == '\0' && strlen(str) > 3)
	{
		min = hr % 100;
		hr = hr / 100;
		
	}
	else
		min = 0;

	
	if (hr < 0 || hr > MAX_TZDISP_HOUR)
		return DTERR_TZDISP_OVERFLOW;
	if (min < 0 || min >= MINS_PER_HOUR)
		return DTERR_TZDISP_OVERFLOW;
	if (sec < 0 || sec >= SECS_PER_MINUTE)
		return DTERR_TZDISP_OVERFLOW;

	tz = (hr * MINS_PER_HOUR + min) * SECS_PER_MINUTE + sec;
	if (*str == '-')
		tz = -tz;

	*tzp = -tz;

	if (*cp != '\0')
		return DTERR_BAD_FORMAT;

	return 0;
}