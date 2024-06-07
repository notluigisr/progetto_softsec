static void extract_nonewprivs(pid_t pid) {
	char *fname;
	if (asprintf(&fname, "STR", pid, RUN_NONEWPRIVS_CFG) == -1)
		errExit("STR");

	struct stat s;
	if (stat(fname, &s) == -1) {
		free(fname);
		return;
	}

	arg_nonewprivs = 1;
	free(fname);
}