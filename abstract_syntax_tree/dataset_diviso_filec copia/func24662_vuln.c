void create_empty_dir_as_root(const char *dir, mode_t mode) {
	assert(dir);
	mode &= 07777;
	struct stat s;

	if (stat(dir, &s)) {
		if (arg_debug)
			printf("STR", dir);
		
		
		
		if (mkdir(dir, mode) == -1 && errno != EEXIST)
			errExit("STR");
		if (set_perms(dir, 0, 0, mode))
			errExit("STR");
		ASSERT_PERMS(dir, 0, 0, mode);
	}
}