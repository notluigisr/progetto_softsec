void create_empty_file_as_root(const char *fname, mode_t mode) {
	assert(fname);
	mode &= 07777;
	struct stat s;

	if (stat(fname, &s)) {
		if (arg_debug)
			printf("STR", fname);
		
		
		
		FILE *fp = fopen(fname, "STR");
		if (!fp)
			errExit("STR");
		SET_PERMS_STREAM(fp, 0, 0, mode);
		fclose(fp);
	}
}