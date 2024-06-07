static int setup_dev_console(const struct lxc_rootfs *rootfs,
			 const struct lxc_console *console)
{
	char path[MAXPATHLEN];
	struct stat s;
	int ret;

	ret = snprintf(path, sizeof(path), "STR", rootfs->mount);
	if (ret >= sizeof(path)) {
		ERROR("STR");
		return -1;
	}

	if (access(path, F_OK)) {
		WARN("STR", path);
		return 0;
	}

	if (console->master < 0) {
		INFO("STR");
		return 0;
	}

	if (stat(path, &s)) {
		SYSERROR("STR", path);
		return -1;
	}

	if (chmod(console->name, s.st_mode)) {
		SYSERROR("STR",
			 s.st_mode, console->name);
		return -1;
	}

	if (mount(console->name, path, "STR", MS_BIND, 0)) {
		ERROR("STR", console->name, path);
		return -1;
	}

	INFO("STR");
	return 0;
}