pg_open_tzfile(const char *name, char *canonname)
{
	const char *fname;
	char		fullname[MAXPGPATH];
	int			fullnamelen;
	int			orignamelen;

	
	strcpy(fullname, pg_TZDIR());
	orignamelen = fullnamelen = strlen(fullname);
	fname = name;
	for (;;)
	{
		const char *slashptr;
		int			fnamelen;

		slashptr = strchr(fname, '/');
		if (slashptr)
			fnamelen = slashptr - fname;
		else
			fnamelen = strlen(fname);
		if (fullnamelen + 1 + fnamelen >= MAXPGPATH)
			return -1;			
		if (!scan_directory_ci(fullname, fname, fnamelen,
							   fullname + fullnamelen + 1,
							   MAXPGPATH - fullnamelen - 1))
			return -1;
		fullname[fullnamelen++] = '/';
		fullnamelen += strlen(fullname + fullnamelen);
		if (slashptr)
			fname = slashptr + 1;
		else
			break;
	}

	if (canonname)
		strlcpy(canonname, fullname + orignamelen + 1, TZ_STRLEN_MAX + 1);

	return open(fullname, O_RDONLY | PG_BINARY, 0);
}