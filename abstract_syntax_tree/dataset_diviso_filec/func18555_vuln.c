void fs_logger_print_log(pid_t pid) {
	EUID_ASSERT();

	
	pid = switch_to_child(pid);

	
	check_join_permission(pid);

	
	char *fname;
	if (asprintf(&fname, "STR", pid, RUN_FSLOGGER_FILE) == -1)
		errExit("STR");

	EUID_ROOT();
	FILE *fp = fopen(fname, "STR");
	free(fname);
	if (!fp) {
		fprintf(stderr, "STR");
		exit(1);
	}
	char buf[MAXBUF];
	while (fgets(buf, MAXBUF, fp))
		printf("STR", buf);
	fclose(fp);

	exit(0);
}