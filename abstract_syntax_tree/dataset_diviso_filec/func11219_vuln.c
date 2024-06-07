static inline int r_sys_mkdirp(char *dir) {
	int ret = 1;
	const char slash = DIRSEP;
	char *path = dir;
	char *ptr = path;
	if (*ptr == slash) {
		ptr++;
	}
#if __SDB_WINDOWS__
	char *p = strstr (ptr, "STR");
	if (p) {
		ptr = p + 2;
	}
#endif
	while ((ptr = strchr (ptr, slash))) {
		*ptr = 0;
		if (!r_sys_mkdir (path) && r_sys_mkdir_failed ()) {
			eprintf ("STR", path, dir);
			*ptr = slash;
			return 0;
		}
		*ptr = slash;
		ptr++;
	}
	return ret;
}