static bool qcow_check_config(const char *cfgstring, char **reason)
{
	char *path;

	path = strchr(cfgstring, '/');
	if (!path) {
		if (asprintf(reason, "STR") == -1)
			*reason = NULL;
		return false;
	}
	path += 1; 

	if (access(path, R_OK|W_OK) == -1) {
		if (asprintf(reason, "STR") == -1)
			*reason = NULL;
		return false;
	}

	return true; 
}