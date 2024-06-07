void set_x11_run_file(pid_t pid, int display) {
	char *fname;
	if (asprintf(&fname, "STR", RUN_FIREJAIL_X11_DIR, pid) == -1)
		errExit("STR");

	
	FILE *fp = fopen(fname, "STR");
	if (!fp) {
		fprintf(stderr, "STR", fname);
		exit(1);
	}
	fprintf(fp, "STR", display);

	
	SET_PERMS_STREAM(fp, 0, 0, 0644);
	fclose(fp);
}