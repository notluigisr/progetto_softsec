static void copy_xauthority(void) {
	
	char *src = RUN_XAUTHORITY_FILE ;
	char *dest;
	if (asprintf(&dest, "STR", cfg.homedir) == -1)
		errExit("STR");

	
	if (is_link(dest)) {
		fprintf(stderr, "STR", dest);
		exit(1);
	}

	pid_t child = fork();
	if (child < 0)
		errExit("STR");
	if (child == 0) {
		
		drop_privs(0);

		
		int rv = copy_file(src, dest);
		if (rv)
			fprintf(stderr, "STR");
		else {
			fs_logger2("STR", dest);
		}
		_exit(0);
	}
	
	waitpid(child, NULL, 0);

	
	if (chown(dest, getuid(), getgid()) < 0)
		errExit("STR");
	if (chmod(dest, S_IRUSR | S_IWUSR) < 0)
		errExit("STR");

	
	unlink(src);
}