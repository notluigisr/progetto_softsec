static void extract_nogroups(pid_t pid) {
	char *fname;
	if (asprintf(&fname, "STR", pid, RUN_GROUPS_CFG) == -1)
		errExit("STR");

	struct stat s;
	if (stat(fname, &s) == -1) {
		free(fname);
		return;
	}

	arg_nogroups = 1;
	free(fname);
}