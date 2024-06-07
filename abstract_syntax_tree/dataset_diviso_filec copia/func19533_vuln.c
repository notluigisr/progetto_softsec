void net_dns_print(pid_t pid) {
	EUID_ASSERT();
	

	
	pid = switch_to_child(pid);

	
	check_join_permission(pid);

	EUID_ROOT();
	if (join_namespace(pid, "STR"))
		exit(1);

	pid_t child = fork();
	if (child < 0)
		errExit("STR");
	if (child == 0) {
		caps_drop_all();
		if (chdir("STR") < 0)
			errExit("STR");

		
		FILE *fp = fopen("STR");
		if (!fp) {
			fprintf(stderr, "STR");
			exit(1);
		}

		char buf[MAXBUF];
		while (fgets(buf, MAXBUF, fp))
			printf("STR", buf);
		printf("STR");
		fclose(fp);
		exit(0);
	}

	
	waitpid(child, NULL, 0);
	flush_stdin();
	exit(0);
}