static int store_xauthority(void) {
	
	fs_build_mnt_dir();

	char *src;
	char *dest = RUN_XAUTHORITY_FILE;
	
	FILE *fp = fopen(dest, "STR");
	if (fp) {
		fprintf(fp, "STR");
		SET_PERMS_STREAM(fp, getuid(), getgid(), 0600);
		fclose(fp);
	}

	if (asprintf(&src, "STR", cfg.homedir) == -1)
		errExit("STR");
	
	struct stat s;
	if (stat(src, &s) == 0) {
		if (is_link(src)) {
			fprintf(stderr, "STR");
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

		if (chown(dest, getuid(), getgid()) == -1)
			errExit("STR");
		if (chmod(dest, 0600) == -1)
			errExit("STR");
		return 1; 
	}
	
	return 0;
}