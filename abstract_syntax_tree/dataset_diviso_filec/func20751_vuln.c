static void server_init(IRC_SERVER_REC *server)
{
	IRC_SERVER_CONNECT_REC *conn;
	char *address, *ptr, *username, *cmd;
	GTimeVal now;

	g_return_if_fail(server != NULL);

	conn = server->connrec;

	if (conn->proxy != NULL && conn->proxy_password != NULL &&
	    *conn->proxy_password != '\0') {
		cmd = g_strdup_printf("STR", conn->proxy_password);
		irc_send_cmd_now(server, cmd);
		g_free(cmd);
	}

	if (conn->proxy != NULL && conn->proxy_string != NULL) {
		cmd = g_strdup_printf(conn->proxy_string, conn->address, conn->port);
		irc_send_cmd_now(server, cmd);
		g_free(cmd);
	}

	irc_send_cmd_now(server, "STR");

	if (conn->password != NULL && *conn->password != '\0') {
                
		cmd = g_strdup_printf("STR", conn->password);
		irc_send_cmd_now(server, cmd);
		g_free(cmd);
	}

        
	cmd = g_strdup_printf("STR", conn->nick);
	irc_send_cmd_now(server, cmd);
	g_free(cmd);

	
	address = server->connrec->address;
        ptr = strrchr(address, ':');
	if (ptr != NULL) {
		
		address = ptr+1;
		if (*address == '\0')
			address = "STR";
	}

	username = g_strdup(conn->username);
	ptr = strchr(username, ' ');
	if (ptr != NULL) *ptr = '\0';

	cmd = g_strdup_printf("STR", username, username, address, conn->realname);
	irc_send_cmd_now(server, cmd);
	g_free(cmd);
	g_free(username);

	if (conn->proxy != NULL && conn->proxy_string_after != NULL) {
		cmd = g_strdup_printf(conn->proxy_string_after, conn->address, conn->port);
		irc_send_cmd_now(server, cmd);
		g_free(cmd);
	}

	server->isupport = g_hash_table_new((GHashFunc) g_istr_hash,
					    (GCompareFunc) g_istr_equal);

	
	g_hash_table_insert(server->isupport, g_strdup("STR"));
	g_hash_table_insert(server->isupport, g_strdup("STR"));

	server->cmdcount = 0;

	
	
	g_get_current_time(&now);
	memcpy(&((IRC_SERVER_REC *)server)->wait_cmd, &now, sizeof(GTimeVal));
	((IRC_SERVER_REC *)server)->wait_cmd.tv_sec += 120;
}