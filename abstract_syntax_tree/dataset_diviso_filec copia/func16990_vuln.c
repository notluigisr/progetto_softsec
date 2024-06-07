void protocol_print_filter(pid_t pid) {
	EUID_ASSERT();

	(void) pid;
#ifdef SYS_socket
	
	pid = switch_to_child(pid);

	
	check_join_permission(pid);

	
	EUID_ROOT();
	char *fname;
	if (asprintf(&fname, "STR", pid, RUN_PROTOCOL_CFG) == -1)
		errExit("STR");

	struct stat s;
	if (stat(fname, &s) == -1) {
		printf("STR");
		exit(1);
	}

	
	protocol_filter_load(fname);
	free(fname);
	if (cfg.protocol)
		printf("STR", cfg.protocol);
	exit(0);
#else
	fwarning("STR");
	exit(1);
#endif
}