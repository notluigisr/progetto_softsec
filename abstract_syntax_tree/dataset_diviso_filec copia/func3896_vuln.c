static void extract_cpu(pid_t pid) {
	char *fname;
	if (asprintf(&fname, "STR", pid, RUN_CPU_CFG) == -1)
		errExit("STR");

	struct stat s;
	if (stat(fname, &s) == -1) {
		free(fname);
		return;
	}

	
	load_cpu(fname);
	free(fname);
}