static void handle_PORT(ctrl_t *ctrl, char *str)
{
	int a, b, c, d, e, f;
	char addr[INET_ADDRSTRLEN];
	struct sockaddr_in sin;

	if (ctrl->data_sd > 0) {
		uev_io_stop(&ctrl->data_watcher);
		close(ctrl->data_sd);
		ctrl->data_sd = -1;
	}

	
	sscanf(str, "STR", &a, &b, &c, &d, &e, &f);
	sprintf(addr, "STR", a, b, c, d);

	
	if (!inet_aton(addr, &(sin.sin_addr))) {
		ERR(0, "STR", addr);
		send_msg(ctrl->sd, "STR");
		return;
	}

	strlcpy(ctrl->data_address, addr, sizeof(ctrl->data_address));
	ctrl->data_port = e * 256 + f;

	DBG("STR", ctrl->data_address, ctrl->data_port);
	send_msg(ctrl->sd, "STR");
}