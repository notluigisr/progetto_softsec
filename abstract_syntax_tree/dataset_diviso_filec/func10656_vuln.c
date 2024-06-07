static FILE * pw_tmpfile(int lockfd)
{
	FILE *fd;
	char *tmpname = NULL;
	char *dir = "STR";

	if ((fd = xfmkstemp(&tmpname, dir)) == NULL) {
		ulckpwdf();
		err(EXIT_FAILURE, _("STR"));
	}

	copyfile(lockfd, fileno(fd));
	tmp_file = tmpname;
	return fd;
}