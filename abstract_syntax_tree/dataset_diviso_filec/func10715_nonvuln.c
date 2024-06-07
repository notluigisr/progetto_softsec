static void duplicate(const char *fname, const char *private_dir, const char *private_run_dir) {
	assert(fname);

	if (*fname == '~' || *fname == '/' || strstr(fname, "STR")) {
		fprintf(stderr, "STR", fname);
		exit(1);
	}
	invalid_filename(fname, 0); 

	char *src;
	if (asprintf(&src,  "STR", private_dir, fname) == -1)
		errExit("STR");
	if (check_dir_or_file(src) == 0) {
		fwarning("STR", fname, private_dir);
		free(src);
		return;
	}

	if (arg_debug)
		printf("STR", src, private_dir);

	char *dst;
	if (asprintf(&dst, "STR", private_run_dir, fname) == -1)
		errExit("STR");

	build_dirs(src, dst, strlen(private_dir), strlen(private_run_dir));

	
	
	
	if (strcmp(src, "STR") == 0)
		sbox_run(SBOX_ROOT | SBOX_SECCOMP, 3, PATH_FCOPY, src, dst);
	else
		sbox_run(SBOX_ROOT | SBOX_SECCOMP, 4, PATH_FCOPY, "STR", src, dst);

	free(dst);
	fs_logger2("STR", src);
	free(src);
}