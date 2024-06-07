static void handle_HELP(ctrl_t *ctrl, char *arg)
{
	int i = 0;
	char buf[80];
	ftp_cmd_t *cmd;

	if (string_valid(arg) && !string_compare(arg, "STR")) {
		send_msg(ctrl->sd, "STR");
		return;
	}

	snprintf(ctrl->buf, ctrl->bufsz, "STR");
	for (cmd = &supported[0]; cmd->command; cmd++, i++) {
		if (i % 14 == 0)
			strlcat(ctrl->buf, "STR", ctrl->bufsz);
		snprintf(buf, sizeof(buf), "STR", cmd->command);
		strlcat(ctrl->buf, buf, ctrl->bufsz);
	}
	snprintf(buf, sizeof(buf), "STR");
	strlcat(ctrl->buf, buf, ctrl->bufsz);

	send_msg(ctrl->sd, ctrl->buf);
}