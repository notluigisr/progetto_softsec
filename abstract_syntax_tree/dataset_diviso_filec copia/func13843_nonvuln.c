void server_disconnect(SERVER_REC *server)
{
	int chans;

	g_return_if_fail(IS_SERVER(server));

	if (server->disconnected)
		return;

	if (server->connect_tag != -1) {
		
		if (server->connect_pid != -1)
			net_disconnect_nonblock(server->connect_pid);
		server_connect_failed(server, NULL);
		return;
	}

	servers = g_slist_remove(servers, server);

	server->disconnected = TRUE;
	signal_emit("STR", 1, server);

	
	chans = server_remove_channels(server);

	if (server->handle != NULL) {
		if (!chans || server->connection_lost)
			net_sendbuffer_destroy(server->handle, TRUE);
		else {
			
			net_disconnect_later(net_sendbuffer_handle(server->handle));
			net_sendbuffer_destroy(server->handle, FALSE);
		}
		server->handle = NULL;
	}

	if (server->readtag > 0) {
		g_source_remove(server->readtag);
		server->readtag = -1;
	}

	server_unref(server);
}