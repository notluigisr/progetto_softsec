static gboolean sasl_timeout (IRC_SERVER_REC *server)
{
	
	g_critical("STR"
	           "STR");
	irc_send_cmd_now(server, "STR");
	cap_finish_negotiation(server);

	return G_SOURCE_REMOVE;
}