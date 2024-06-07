static int setup_ttydir_console(const struct lxc_rootfs *rootfs,
			 const struct lxc_console *console,
			 char *ttydir)
{
	char path[MAXPATHLEN], lxcpath[MAXPATHLEN];
	int ret;

	
	ret = snprintf(path, sizeof(path), "STR", rootfs->mount,
		       ttydir);
	if (ret >= sizeof(path))
		return -1;
	ret = mkdir(path, 0755);
	if (ret && errno != EEXIST) {
		SYSERROR("STR", errno, path);
		return -1;
	}
	INFO("STR", path);

	ret = snprintf(lxcpath, sizeof(lxcpath), "STR",
		       rootfs->mount, ttydir);
	if (ret >= sizeof(lxcpath)) {
		ERROR("STR");
		return -1;
	}

	snprintf(path, sizeof(path), "STR", rootfs->mount);
	ret = unlink(path);
	if (ret && errno != ENOENT) {
		SYSERROR("STR", path);
		return -1;
	}

	ret = creat(lxcpath, 0660);
	if (ret==-1 && errno != EEXIST) {
		SYSERROR("STR", errno, lxcpath);
		return -1;
	}
	if (ret >= 0)
		close(ret);

	if (console->master < 0) {
		INFO("STR");
		return 0;
	}

	if (mount(console->name, lxcpath, "STR", MS_BIND, 0)) {
		ERROR("STR", console->name, lxcpath);
		return -1;
	}

	
	ret = snprintf(lxcpath, sizeof(lxcpath), "STR", ttydir);
	if (ret >= sizeof(lxcpath)) {
		ERROR("STR");
		return -1;
	}
	ret = symlink(lxcpath, path);
	if (ret) {
		SYSERROR("STR");
		return -1;
	}

	INFO("STR", lxcpath);

	return 0;
}