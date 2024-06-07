static int proc_parse_options(char *options, struct pid_namespace *pid)
{
	char *p;
	substring_t args[MAX_OPT_ARGS];

	pr_debug("STR", options);

	if (!options)
		return 1;

	while ((p = strsep(&options, "STR")) != NULL) {
		int token;
		if (!*p)
			continue;

		args[0].to = args[0].from = 0;
		token = match_token(p, tokens, args);
		switch (token) {
		default:
			pr_err("STR"
			       "STR", p);
			return 0;
		}
	}

	return 1;
}