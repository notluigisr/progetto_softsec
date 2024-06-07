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
			return 0;
		}

		copy_file_as_user(src, dest, getuid(), getgid(), 0600);
		fs_logger2("STR", dest);
		return 1; 
	}
	
	return 0;
}