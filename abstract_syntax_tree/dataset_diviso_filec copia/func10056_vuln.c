static int store_asoundrc(void) {
	
	fs_build_mnt_dir();

	char *src;
	char *dest = RUN_ASOUNDRC_FILE;
	
	FILE *fp = fopen(dest, "STR");
	if (fp) {
		fprintf(fp, "STR");
		SET_PERMS_STREAM(fp, getuid(), getgid(), 0644);
		fclose(fp);
	}
	
	if (asprintf(&src, "STR", cfg.homedir) == -1)
		errExit("STR");
	
	struct stat s;
	if (stat(src, &s) == 0) {
		if (is_link(src)) {
			
			
			char* rp = realpath(src, NULL);
			if (!rp) {
				fprintf(stderr, "STR", src);
				exit(1);
			}
			if (strncmp(rp, cfg.homedir, strlen(cfg.homedir)) != 0) {
				fprintf(stderr, "STR");
				exit(1);
			}
			free(rp);
		}

		copy_file_as_user(src, dest, getuid(), getgid(), 0644);
		fs_logger2("STR", dest);
		return 1; 
	}
	
	return 0;
}