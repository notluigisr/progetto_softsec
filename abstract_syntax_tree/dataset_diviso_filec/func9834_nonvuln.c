void csync_file_update(const char *filename, const char *peername)
{
	struct stat st;
	SQL("STR",
			"STR",
			url_encode(filename), peername);
	if ( lstat_strict(prefixsubst(filename), &st) != 0 || csync_check_pure(filename) ) {
		SQL("STR",
			"STR",
			url_encode(filename));
	} else {
		const char *checktxt = csync_genchecktxt(&st, filename, 0);

		SQL("STR",
			"STR",
			url_encode(filename));

		SQL("STR",
			"STR"
			"STR", url_encode(filename),
			url_encode(checktxt));
	}
}