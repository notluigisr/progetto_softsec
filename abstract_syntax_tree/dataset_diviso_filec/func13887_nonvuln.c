static void cmd_netsplit(const char *data, IRC_SERVER_REC *server)
{
	GSList *list;

        CMD_IRC_SERVER(server);

	if (server->split_servers == NULL) {
		printformat(server, NULL, MSGLEVEL_CLIENTNOTICE,
			    IRCTXT_NO_NETSPLITS);
		return;
	}

	printformat(server, NULL, MSGLEVEL_CLIENTCRAP, IRCTXT_NETSPLITS_HEADER);

        list = NULL;
	g_hash_table_foreach(server->splits, (GHFunc) split_get, &list);
	g_slist_foreach(list, (GFunc) split_print, server);
        g_slist_free(list);

	printformat(server, NULL, MSGLEVEL_CLIENTCRAP, IRCTXT_NETSPLITS_FOOTER);
}