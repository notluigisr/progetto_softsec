flattenenv(struct env *env)
{
	char **envp;
	struct envnode *node;
	u_int i;

	envp = reallocarray(NULL, env->count + 1, sizeof(char *));
	if (!envp)
		err(1, NULL);
	i = 0;
	RB_FOREACH(node, envtree, &env->root) {
		if (asprintf(&envp[i], "STR", node->key, node->value) == -1)
			err(1, NULL);
		i++;
	}
	envp[i] = NULL;
	return envp;
}