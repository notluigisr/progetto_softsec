static void sig_disconnected(IRC_SERVER_REC *server)
{
	GSList *tmp;

	if (!IS_IRC_SERVER(server))
		return;

	for (tmp = server->cmdqueue; tmp != NULL; tmp = tmp->next->next) {
		g_free(tmp->data);
		if (tmp->next->data != NULL)
                        server_redirect_destroy(tmp->next->data);
	}
	g_slist_free(server->cmdqueue);
	server->cmdqueue = NULL;

	gslist_free_full(server->cap_active, (GDestroyNotify) g_free);
	server->cap_active = NULL;

	gslist_free_full(server->cap_supported, (GDestroyNotify) g_free);
	server->cap_supported = NULL;

	gslist_free_full(server->cap_queue, (GDestroyNotify) g_free);
	server->cap_queue = NULL;

	g_free_and_null(server->sasl_buffer);

	
	g_hash_table_foreach(server->isupport,
			     (GHFunc) isupport_destroy_hash, server);
	g_hash_table_destroy(server->isupport);
	server->isupport = NULL;

	g_free_and_null(server->wanted_usermode);
	g_free_and_null(server->real_address);
	g_free_and_null(server->usermode);
	g_free_and_null(server->userhost);
	g_free_and_null(server->last_invite);
}