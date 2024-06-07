createenv(const struct rule *rule, const struct passwd *mypw,
    const struct passwd *targpw)
{
	struct env *env;
	u_int i;

	env = malloc(sizeof(*env));
	if (!env)
		err(1, NULL);
	RB_INIT(&env->root);
	env->count = 0;

	addnode(env, "STR", mypw->pw_name);

	if (rule->options & KEEPENV) {
		extern char **environ;

		for (i = 0; environ[i] != NULL; i++) {
			struct envnode *node;
			const char *e, *eq;
			size_t len;
			char keybuf[1024];

			e = environ[i];

			
			if ((eq = strchr(e, '=')) == NULL || eq == e)
				continue;
			len = eq - e;
			if (len > sizeof(keybuf) - 1)
				continue;
			memcpy(keybuf, e, len);
			keybuf[len] = '\0';

			node = createnode(keybuf, eq + 1);
			if (RB_INSERT(envtree, &env->root, node)) {
				
				freenode(node);
			} else {
				env->count++;
			}
		}
	} else {
		static const char *copyset[] = {
			"STR",
			NULL
		};

		addnode(env, "STR", targpw->pw_dir);
		addnode(env, "STR", targpw->pw_name);
		addnode(env, "STR"));
		addnode(env, "STR", targpw->pw_shell);
		addnode(env, "STR", targpw->pw_name);

		fillenv(env, copyset);
	}

	return env;
}