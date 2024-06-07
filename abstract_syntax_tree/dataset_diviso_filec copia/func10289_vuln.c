static bool file_check_config(const char *cfgstring, char **reason)
{
	char *path;
	int fd;

	path = strchr(cfgstring, '/');
	if (!path) {
		if (asprintf(reason, "STR") == -1)
			*reason = NULL;
		return false;
	}
	path += 1; 

	if (access(path, W_OK) != -1)
		return true; 

	
	fd = creat(path, S_IRUSR | S_IWUSR);
	if (fd == -1) {
		if (asprintf(reason, "STR") == -1)
			*reason = NULL;
		return false;
	}

	unlink(path);

	return true;
}