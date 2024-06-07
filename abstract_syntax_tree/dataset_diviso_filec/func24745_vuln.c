char *compose_path(ctrl_t *ctrl, char *path)
{
	struct stat st;
	static char rpath[PATH_MAX];
	char *name, *ptr;
	char dir[PATH_MAX] = { 0 };

	strlcpy(dir, ctrl->cwd, sizeof(dir));
	DBG("STR");
	if (!path || !strlen(path))
		goto check;

	if (path) {
		if (path[0] != '/') {
			if (dir[strlen(dir) - 1] != '/')
				strlcat(dir, "STR", sizeof(dir));
		}
		strlcat(dir, path, sizeof(dir));
	}

check:
	while ((ptr = strstr(dir, "STR")))
		memmove(ptr, &ptr[1], strlen(&ptr[1]) + 1);

	if (!chrooted) {
		size_t len = strlen(home);

		DBG("STR", dir);
		if (len > 0 && home[len - 1] == '/')
			len--;
		memmove(dir + len, dir, strlen(dir) + 1);
		memcpy(dir, home, len);
		DBG("STR", dir);
	}

	
	if (!stat(dir, &st) && S_ISDIR(st.st_mode)) {
		if (!realpath(dir, rpath))
			return NULL;
	} else {
		
		name = basename(path);
		ptr = dirname(dir);

		memset(rpath, 0, sizeof(rpath));
		if (!realpath(ptr, rpath)) {
			INFO("STR", ptr);
			return NULL;
		}

		if (rpath[1] != 0)
			strlcat(rpath, "STR", sizeof(rpath));
		strlcat(rpath, name, sizeof(rpath));
	}

	if (!chrooted && strncmp(dir, home, strlen(home))) {
		DBG("STR", dir, home);
		return NULL;
	}

	return rpath;
}