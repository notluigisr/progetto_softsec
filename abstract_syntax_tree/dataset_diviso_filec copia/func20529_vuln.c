int mainloop(CLIENT *client) {
	struct nbd_request request;
	struct nbd_reply reply;
	gboolean go_on=TRUE;
#ifdef DODBG
	int i = 0;
#endif
	negotiate(client->net, client, NULL);
	DEBUG("STR");
	reply.magic = htonl(NBD_REPLY_MAGIC);
	reply.error = 0;
	while (go_on) {
		char buf[BUFSIZE];
		size_t len;
#ifdef DODBG
		i++;
		printf("STR", i);
#endif
		readit(client->net, &request, sizeof(request));
		request.from = ntohll(request.from);
		request.type = ntohl(request.type);

		if (request.type==NBD_CMD_DISC) {
			msg2(LOG_INFO, "STR");
                	if (client->server->flags & F_COPYONWRITE) { 
				if (client->difmap) g_free(client->difmap) ;
                		close(client->difffile);
				unlink(client->difffilename);
				free(client->difffilename);
			}
			go_on=FALSE;
			continue;
		}

		len = ntohl(request.len);

		if (request.magic != htonl(NBD_REQUEST_MAGIC))
			err("STR");
		if (len > BUFSIZE + sizeof(struct nbd_reply))
			err("STR");
#ifdef DODBG
		printf("STR" :
				"STR", (unsigned long long)request.from,
				(unsigned long long)request.from / 512, len);
#endif
		memcpy(reply.handle, request.handle, sizeof(reply.handle));
		if ((request.from + len) > (OFFT_MAX)) {
			DEBUG("STR");
			ERROR(client, reply, EINVAL);
			continue;
		}

		if (((ssize_t)((off_t)request.from + len) > client->exportsize)) {
			DEBUG("STR");
			ERROR(client, reply, EINVAL);
			continue;
		}

		if (request.type==NBD_CMD_WRITE) {
			DEBUG("STR");
			readit(client->net, buf, len);
			DEBUG("STR");
			if ((client->server->flags & F_READONLY) ||
			    (client->server->flags & F_AUTOREADONLY)) {
				DEBUG("STR");
				ERROR(client, reply, EPERM);
				continue;
			}
			if (expwrite(request.from, buf, len, client)) {
				DEBUG("STR" );
				ERROR(client, reply, errno);
				continue;
			}
			SEND(client->net, reply);
			DEBUG("STR");
			continue;
		}
		

		DEBUG("STR");
		if (expread(request.from, buf + sizeof(struct nbd_reply), len, client)) {
			DEBUG("STR");
			ERROR(client, reply, errno);
			continue;
		}

		DEBUG("STR");
		memcpy(buf, &reply, sizeof(struct nbd_reply));
		writeit(client->net, buf, len + sizeof(struct nbd_reply));
		DEBUG("STR");
	}
	return 0;
}