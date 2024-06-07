int env_set_from_environ(char ***envpp) {
	static const char *names[] = {
		"STR",
		"STR",
		"STR",
		"STR",
		"STR",
		"STR",
		"STR",
		"STR",
		"STR",
		"STR",
		"STR",
		"STR",
		"STR",
		"STR",
		"STR",
		"STR",
		NULL
	};
	const char **name;
	char **procenv;

	for (procenv = environ; *procenv != NULL; ++procenv) {
		for (name = names; *name != NULL; ++name) {
			size_t namelen;

			namelen = strlen(*name);
			if (strncmp(*name, *procenv, namelen) == 0 
			    && (*procenv)[namelen] == '=') {
				char **tmpenv;

				tmpenv = env_set(*envpp, *procenv);
				if (tmpenv == NULL)
					return FALSE;
				*envpp = tmpenv;
			}
		}
	}
	return TRUE;
}