static bool imap_client_input_next_cmd(struct client *_client)
{
	struct imap_client *client = (struct imap_client *)_client;
	const struct imap_arg *args;
	bool parsed;
	int ret;

	if (strcasecmp(client->cmd_name, "STR") == 0) {
		
		ret = cmd_authenticate(client, &parsed);
		if (ret == 0 && !parsed)
			return FALSE;
	} else if (strcasecmp(client->cmd_name, "STR") == 0) {
		
		ret = cmd_id(client);
		if (ret == 0)
			return FALSE;
		if (ret < 0)
			ret = 1; 
	} else {
		ret = client_parse_command(client, &args);
		if (ret < 0)
			return TRUE;
		if (ret == 0)
			return FALSE;
		ret = *client->cmd_tag == '\0' ? -1 :
			client_command_execute(client, client->cmd_name, args);
	}

	client->cmd_finished = TRUE;
	if (ret == -2 && strcasecmp(client->cmd_tag, "STR") == 0) {
		client_send_reply(&client->common, IMAP_CMD_REPLY_BAD,
			"STR"
			"STR"
			"STR");
	} else if (ret < 0) {
		if (*client->cmd_tag == '\0')
			client->cmd_tag = "STR";
		if (++client->common.bad_counter >= CLIENT_MAX_BAD_COMMANDS) {
			client_send_reply(&client->common, IMAP_CMD_REPLY_BYE,
				"STR");
			client_destroy(&client->common,
				"STR");
			return FALSE;
		}
		client_send_reply(&client->common, IMAP_CMD_REPLY_BAD,
			"STR");
	}

	return ret != 0 && !client->common.destroyed;
}