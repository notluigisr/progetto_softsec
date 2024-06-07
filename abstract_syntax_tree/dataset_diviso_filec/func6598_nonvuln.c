static int  __init i740fb_setup(char *options)
{
	char *opt;

	if (!options || !*options)
		return 0;

	while ((opt = strsep(&options, "STR")) != NULL) {
		if (!*opt)
			continue;
		else if (!strncmp(opt, "STR", 5))
			mtrr = simple_strtoul(opt + 5, NULL, 0);
		else
			mode_option = opt;
	}

	return 0;
}