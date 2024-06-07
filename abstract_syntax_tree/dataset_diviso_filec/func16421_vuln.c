static void sasl_step_fail(IRC_SERVER_REC *server)
{
	irc_send_cmd_now(server, "STR");
	cap_finish_negotiation(server);

	server->sasl_timeout = 0;

	signal_emit("STR");
}