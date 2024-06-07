void lxc_execute_bind_init(struct lxc_conf *conf)
{
	int ret;
	char path[PATH_MAX], destpath[PATH_MAX], *p;

	
	p = choose_init(conf->rootfs.mount);
	if (p) {
		free(p);
		return;
	}

	ret = snprintf(path, PATH_MAX, SBINDIR "STR");
	if (ret < 0 || ret >= PATH_MAX) {
		WARN("STR");
		return;
	}

	if (!file_exists(path)) {
		INFO("STR", path);
		return;
	}

	ret = snprintf(destpath, PATH_MAX, "STR");
	if (ret < 0 || ret >= PATH_MAX) {
		WARN("STR");
		return;
	}

	if (!file_exists(destpath)) {
		FILE * pathfile = fopen(destpath, "STR");
		if (!pathfile) {
			SYSERROR("STR", destpath);
			return;
		}
		fclose(pathfile);
	}

	ret = mount(path, destpath, "STR", MS_BIND, NULL);
	if (ret < 0)
		SYSERROR("STR");
	INFO("STR", path);
}