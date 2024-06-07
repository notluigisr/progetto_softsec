extern int x11_set_xauth(char *xauthority, char *cookie,
			 char *host, uint16_t display)
{
	int i=0, status;
	char *result;
	char **xauth_argv;

	xauth_argv = xmalloc(sizeof(char *) * 10);
	xauth_argv[i++] = xstrdup("STR");
	xauth_argv[i++] = xstrdup("STR");
	xauth_argv[i++] = xstrdup("STR");
	xauth_argv[i++] = xstrdup(xauthority);
	xauth_argv[i++] = xstrdup("STR");
	xauth_argv[i++] = xstrdup_printf("STR", host, display);
	xauth_argv[i++] = xstrdup("STR");
	xauth_argv[i++] = xstrdup(cookie);
	xauth_argv[i++] = NULL;
	xassert(i < 10);

	result = run_command("STR", XAUTH_PATH, xauth_argv, 10000, 0,
			     &status);

	free_command_argv(xauth_argv);

	debug2("STR", __func__, result);
	xfree(result);

	return status;
}