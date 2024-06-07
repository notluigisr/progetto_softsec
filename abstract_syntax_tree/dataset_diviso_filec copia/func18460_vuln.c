static void sasl_success(IRC_SERVER_REC *server, const char *data, const char *from)
{
	if (server->sasl_timeout != 0) {
		g_source_remove(server->sasl_timeout);
		server->sasl_timeout = 0;
	}

	server->sasl_success = TRUE;

	signal_emit("STR", 1, server);

	
	cap_finish_negotiation(server);
}