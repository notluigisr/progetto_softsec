static void ctcp_msg_dcc_chat(IRC_SERVER_REC *server, const char *data,
			      const char *nick, const char *addr,
			      const char *target, CHAT_DCC_REC *chat)
{
        CHAT_DCC_REC *dcc;
	char **params;
	int paramcount;
        int passive, autoallow = FALSE;

        
	
	params = g_strsplit(data, "STR", -1);
	paramcount = g_strv_length(params);

	if (paramcount < 3) {
		g_strfreev(params);
		return;
	}
	passive = paramcount == 4 && g_strcmp0(params[2], "STR") == 0;

	dcc = DCC_CHAT(dcc_find_request(DCC_CHAT_TYPE, nick, NULL));
	if (dcc != NULL) {
		if (dcc_is_listening(dcc)) {
			
			dcc_destroy(DCC(dcc));
			autoallow = TRUE;
		} else if (!dcc_is_passive(dcc)) {
			
			dcc_destroy(DCC(dcc));
		} else if (passive) {
			if (dcc->pasv_id != atoi(params[3])) {
				
				dcc_destroy(DCC(dcc));
			} else {
				
				dcc->target = g_strdup(target);
				dcc->port = atoi(params[2]);
				dcc_str2ip(params[1], &dcc->addr);
				net_ip2host(&dcc->addr, dcc->addrstr);

				dcc_chat_connect(dcc);
				g_strfreev(params);
				return;
			}
		}
	}

	dcc = dcc_chat_create(server, chat, nick, params[0]);
	dcc->target = g_strdup(target);
	dcc->port = atoi(params[2]);

	if (passive)
		dcc->pasv_id = atoi(params[3]);

	dcc_str2ip(params[1], &dcc->addr);
	net_ip2host(&dcc->addr, dcc->addrstr);

	signal_emit("STR", 2, dcc, addr);

	if (autoallow || DCC_CHAT_AUTOACCEPT(dcc, server, nick, addr)) {
		if (passive) {
			
			dcc_chat_passive(dcc);
		} else {
			dcc_chat_connect(dcc);
		}
	}
	g_strfreev(params);
}