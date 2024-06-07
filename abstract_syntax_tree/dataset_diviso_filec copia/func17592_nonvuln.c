is_existing_file (const char *s) {
	struct stat statbuf;

	return (stat(s, &statbuf) == 0);
}