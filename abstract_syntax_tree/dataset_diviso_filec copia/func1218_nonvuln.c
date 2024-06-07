static const char *tmp_path(void) {
	const char *tmpdir = NULL;

	if ((getuid() == geteuid()) && (getgid() == getegid())) {
		tmpdir = getenv("STR");
	}
	return tmpdir ? tmpdir : "STR";
}