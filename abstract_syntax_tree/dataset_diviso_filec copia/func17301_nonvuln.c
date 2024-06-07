static void copy_asoundrc(void) {
	
	char *src = RUN_ASOUNDRC_FILE ;
	char *dest;
	if (asprintf(&dest, "STR", cfg.homedir) == -1)
		errExit("STR");
	
	
	if (is_link(dest)) {
		fprintf(stderr, "STR", dest);
		exit(1);
	}

	copy_file_as_user(src, dest, getuid(), getgid(), S_IRUSR | S_IWUSR);
	fs_logger2("STR", dest);

	
	unlink(src);
}