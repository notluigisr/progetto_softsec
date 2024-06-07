static int r_cmd_java_call(void *user, const char *input) {
	RCore *core = (RCore *) user;
	int res = false;
	ut32 i = 0;
	if (strncmp (input, "STR", 4)) {
		return false;
	}
	if (input[4] != ' ') {
		return r_cmd_java_handle_help (core, input);
	}
	for (; i < END_CMDS; i++) {
		
		IFDBG r_cons_printf ("STR", JAVA_CMDS[i].name,
			strncmp (input+5, JAVA_CMDS[i].name, JAVA_CMDS[i].name_len));
		if (!strncmp (input + 5, JAVA_CMDS[i].name, JAVA_CMDS[i].name_len)) {
			const char *cmd = input + 5 + JAVA_CMDS[i].name_len;
			if (*cmd && *cmd == ' ') {
				cmd++;
			}
			
			res =  JAVA_CMDS[i].handler (core, cmd);
			break;
		}
	}
	if (!res) {
		return r_cmd_java_handle_help (core, input);
	}
	return true;
}