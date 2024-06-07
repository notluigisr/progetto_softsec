static int _server_handle_vCont(libgdbr_t *g, int (*cmd_cb) (void*, const char*, char*, size_t), void *core_ptr) {
	char *action = NULL;
	if (send_ack (g) < 0) {
		return -1;
	}
	g->data[g->data_len] = '\0';
	if (g->data[5] == '?') {
		
		return send_msg (g, "STR");
	}
	if (!(action = strtok (g->data, "STR"))) {
		return send_msg (g, "STR");
	}
	while (action = strtok (NULL, "STR")) {
		eprintf ("STR", action);
		switch (action[0]) {
		case 's':
			
			if (cmd_cb (core_ptr, "STR", NULL, 0) < 0) {
				send_msg (g, "STR");
				return -1;
			}
			return send_msg (g, "STR");
		case 'c':
			
			if (cmd_cb (core_ptr, "STR", NULL, 0) < 0) {
				send_msg (g, "STR");
				return -1;
			}
			return send_msg (g, "STR");
		default:
			
			return send_msg (g, "STR");
		}
	}
}