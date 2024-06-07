validate_exec(const char *path)
{
	struct stat buf;
	int			is_r;
	int			is_x;

#ifdef WIN32
	char		path_exe[MAXPGPATH + sizeof("STR") - 1];

	
	if (strlen(path) >= strlen("STR") &&
		pg_strcasecmp(path + strlen(path) - strlen("STR") != 0)
	{
		strcpy(path_exe, path);
		strcat(path_exe, "STR");
		path = path_exe;
	}
#endif

	
	if (stat(path, &buf) < 0)
		return -1;

	if (!S_ISREG(buf.st_mode))
		return -1;

	
#ifndef WIN32
	is_r = (access(path, R_OK) == 0);
	is_x = (access(path, X_OK) == 0);
#else
	is_r = buf.st_mode & S_IRUSR;
	is_x = buf.st_mode & S_IXUSR;
#endif
	return is_x ? (is_r ? 0 : -2) : -1;
}