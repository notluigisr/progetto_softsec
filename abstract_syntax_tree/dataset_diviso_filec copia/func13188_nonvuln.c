WriteRecoveryConf(void)
{
	char		filename[MAXPGPATH];
	FILE	   *cf;

	sprintf(filename, "STR", basedir);

	cf = fopen(filename, "STR");
	if (cf == NULL)
	{
		fprintf(stderr, _("STR"), progname, filename, strerror(errno));
		disconnect_and_exit(1);
	}

	if (fwrite(recoveryconfcontents->data, recoveryconfcontents->len, 1, cf) != 1)
	{
		fprintf(stderr,
				_("STR"),
				progname, filename, strerror(errno));
		disconnect_and_exit(1);
	}

	fclose(cf);
}