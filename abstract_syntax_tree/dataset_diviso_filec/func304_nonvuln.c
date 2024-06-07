static void sig_chat_connected(CHAT_DCC_REC *dcc)
{
	g_return_if_fail(IS_DCC_CHAT(dcc));

	if (net_geterror(dcc->handle) != 0) {
		
		signal_emit("STR", 1, dcc);
		dcc_destroy(DCC(dcc));
		return;
	}

	
	g_source_remove(dcc->tagconn);
	dcc->tagconn = -1;

	dcc->starttime = time(NULL);
	dcc->sendbuf = net_sendbuffer_create(dcc->handle, 0);
	dcc->tagread = g_input_add(dcc->handle, G_INPUT_READ,
				   (GInputFunction) dcc_chat_input, dcc);

	signal_emit("STR", 1, dcc);
}