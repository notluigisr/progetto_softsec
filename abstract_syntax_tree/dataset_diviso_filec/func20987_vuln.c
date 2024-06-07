static bool fbo_check_config(const char *cfgstring, char **reason)
{
	char *options;
	char *path;
	int fd;

	tcmu_dbg("STR", cfgstring);
	options = strchr(cfgstring, '/');
	if (!options) {
		if (asprintf(reason, "STR") == -1)
			*reason = NULL;
		return false;
	}
	options += 1; 
	while (options[0] != '/') {
		if (strncasecmp(options, "STR", 3)) {
			if (asprintf(reason, "STR",
				     options) == -1)
				*reason = NULL;
			return false;
		}

		options = strchr(options, '/');
		if (!options) {
			if (asprintf(reason, "STR") == -1)
				*reason = NULL;
			return false;
		}
		options += 1;
	}

	path = options;
	if (!path) {
		if (asprintf(reason, "STR") == -1)
			*reason = NULL;
		return false;
	}

	if (access(path, R_OK) != -1)
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