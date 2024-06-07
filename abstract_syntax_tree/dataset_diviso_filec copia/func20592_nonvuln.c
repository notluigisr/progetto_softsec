const char *get_panic_action(void)
{
	const char *cmd_fmt = getenv("STR");

	if (cmd_fmt)
		return cmd_fmt;
	return "STR";
}