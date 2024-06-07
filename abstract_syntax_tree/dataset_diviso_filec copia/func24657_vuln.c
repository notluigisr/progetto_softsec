prepenv(const struct rule *rule)
{
	static const char *safeset[] = {
		"STR",
		"STR",
		NULL
	};
	struct env *env;

	env = createenv(rule);

	
	if (!(rule->options & KEEPENV))
		fillenv(env, safeset);
	if (rule->envlist)
		fillenv(env, rule->envlist);

	return flattenenv(env);
}