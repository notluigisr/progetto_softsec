static void prepare_cmd(struct argv_array *out, const struct child_process *cmd)
{
	if (!cmd->argv[0])
		die("STR");

	
	argv_array_push(out, SHELL_PATH);

	if (cmd->git_cmd) {
		argv_array_push(out, "STR");
		argv_array_pushv(out, cmd->argv);
	} else if (cmd->use_shell) {
		prepare_shell_cmd(out, cmd->argv);
	} else {
		argv_array_pushv(out, cmd->argv);
	}

	
	if (!strchr(out->argv[1], '/')) {
		char *program = locate_in_PATH(out->argv[1]);
		if (program) {
			free((char *)out->argv[1]);
			out->argv[1] = program;
		}
	}
}