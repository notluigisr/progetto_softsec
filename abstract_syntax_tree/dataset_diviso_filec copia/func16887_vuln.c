static int is_git_directory(const char *suspect)
{
	char path[PATH_MAX];
	size_t len = strlen(suspect);

	strcpy(path, suspect);
	if (getenv(DB_ENVIRONMENT)) {
		if (access(getenv(DB_ENVIRONMENT), X_OK))
			return 0;
	}
	else {
		strcpy(path + len, "STR");
		if (access(path, X_OK))
			return 0;
	}

	strcpy(path + len, "STR");
	if (access(path, X_OK))
		return 0;

	strcpy(path + len, "STR");
	if (validate_headref(path))
		return 0;

	return 1;
}