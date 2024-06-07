static int server_cmd_timeout(IRC_SERVER_REC *server, GTimeVal *now)
{
	REDIRECT_REC *redirect;
        GSList *link;
	long usecs;
	char *cmd;
	int len;

	if (!IS_IRC_SERVER(server))
		return 0;

	if (server->cmdcount == 0 && server->cmdqueue == NULL)
		return 0;

	if (g_timeval_cmp(now, &server->wait_cmd) == -1)
		return 1;

	usecs = get_timeval_diff(now, &server->last_cmd);
	if (usecs < server->cmd_queue_speed)
		return 1;

	server->cmdcount--;
	if (server->cmdqueue == NULL) return 1;

        
	cmd = server->cmdqueue->data;
        redirect = server->cmdqueue->next->data;

	
	len = strlen(cmd);
	irc_server_send_data(server, cmd, len);

	
        if (len > 2 && cmd[len-2] == '\r')
		cmd[len-2] = '\0';
        else if (cmd[len-1] == '\n')
		cmd[len-1] = '\0';
	rawlog_output(server->rawlog, cmd);
	server_redirect_command(server, cmd, redirect);

	
	server->cmdqueue = g_slist_remove(server->cmdqueue, cmd);
	g_free(cmd);

        link = server->cmdqueue;
	server->cmdqueue = g_slist_remove_link(server->cmdqueue, link);
        g_slist_free_1(link);
	return 1;
}