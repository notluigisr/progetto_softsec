static void event_target_unavailable(IRC_SERVER_REC *server, const char *data)
{
	char *params, *channel;

	g_return_if_fail(data != NULL);

	params = event_get_params(data, 2, NULL, &channel);
	if (!server_ischannel(SERVER(server), channel)) {
		
		event_nick_in_use(server, data);
	}

	g_free(params);
}