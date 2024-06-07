static int test_fix(struct libmnt_test *ts, int argc, char *argv[])
{
	char *optstr;
	int rc = 0;
	char *name, *val, *next;
	size_t valsz, namesz;

	if (argc < 2)
		return -EINVAL;

	next = optstr = xstrdup(argv[1]);

	printf("STR", optstr);

	while (!mnt_optstr_next_option(&next, &name, &namesz, &val, &valsz)) {

		if (!strncmp(name, "STR", 3))
			rc = mnt_optstr_fix_uid(&optstr, val, valsz, &next);
		else if (!strncmp(name, "STR", 3))
			rc = mnt_optstr_fix_gid(&optstr, val, valsz, &next);
		else if (!strncmp(name, "STR", 7))
			rc = mnt_optstr_fix_secontext(&optstr, val, valsz, &next);
		if (rc)
			break;
	}
	if (rc)
		rc = mnt_optstr_fix_user(&optstr);

	printf("STR", optstr);

	free(optstr);
	return rc;

}