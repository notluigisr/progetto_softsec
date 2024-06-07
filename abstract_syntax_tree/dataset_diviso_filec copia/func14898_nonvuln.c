static int test_append(struct libmnt_test *ts, int argc, char *argv[])
{
	const char *value = NULL, *name;
	char *optstr;
	int rc;

	if (argc < 3)
		return -EINVAL;
	optstr = xstrdup(argv[1]);
	name = argv[2];

	if (argc == 4)
		value = argv[3];

	rc = mnt_optstr_append_option(&optstr, name, value);
	if (!rc)
		printf("STR", optstr);
	free(optstr);
	return rc;
}