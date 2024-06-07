static void extract_cgroup(pid_t pid) {
	char *fname;
	if (asprintf(&fname, "STR", pid, RUN_CGROUP_CFG) == -1)
		errExit("STR");

	struct stat s;
	if (stat(fname, &s) == -1) {
		free(fname);
		return;
	}

	
	load_cgroup(fname);
	free(fname);
}