static void extract_umask(pid_t pid) {
	char *fname;
	if (asprintf(&fname, "STR", pid, RUN_UMASK_FILE) == -1)
		errExit("STR");

	FILE *fp = fopen(fname, "STR");
	free(fname);
	if (!fp) {
		fprintf(stderr, "STR");
		exit(1);
	}
	if (fscanf(fp, "STR", &orig_umask) != 1) {
		fprintf(stderr, "STR");
		exit(1);
	}
	fclose(fp);
}