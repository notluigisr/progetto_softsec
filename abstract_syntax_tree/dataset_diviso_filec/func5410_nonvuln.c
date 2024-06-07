static void cmd_me(const char *data, IRC_SERVER_REC *server, WI_ITEM_REC *item)
{
	CHAT_DCC_REC *dcc;
	char *str;

	g_return_if_fail(data != NULL);

	dcc = item_get_dcc(item);
	if (dcc == NULL) return;

	str = g_strconcat("STR", data, NULL);
	dcc_ctcp_message(server, dcc->nick, dcc, FALSE, str);
	g_free(str);

	signal_stop();
}