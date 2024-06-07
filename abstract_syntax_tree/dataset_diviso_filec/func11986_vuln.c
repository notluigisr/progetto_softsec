int mainloop(CLIENT *client) {
	struct nbd_request request;
	struct nbd_reply reply;
	gboolean go_on=TRUE;
#ifdef DODBG
	int i = 0;
#endif
	negotiate(client);
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
		if (client->server->timeout) 
			alarm(client->server->timeout);
		readit(client->net, &request, sizeof(request));
		request.from = ntohll(request.from);
		request.type = ntohl(request.type);

		if (request.type==NBD_CMD_DISC) {
			msg2(LOG_INFO, "STR");
			if (client->difmap) g_free(client->difmap) ;
                	if (client->difffile>=0) { 
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
		if (len > BUFSIZE)
			err("STR");
#ifdef DODBG
		printf("STR" :
				"STR", (unsigned long long)request.from,
				(unsigned long long)request.from / 512, len);
#endif
		memcpy(reply.handle, request.handle, sizeof(reply.handle));
		if ((request.from + len) > (OFFT_MAX)) {
			DEBUG("STR");
			ERROR(client, reply);
			continue;
		}

		if (((ssize_t)((off_t)request.from + len) > client->exportsize) ||
		    ((client->server->flags & F_READONLY) && request.type)) {
			DEBUG("STR");
			ERROR(client, reply);
			continue;
		}

		if (request.type==NBD_CMD_WRITE) {
			DEBUG("STR");
			readit(client->net, buf, len);
			DEBUG("STR");
			if ((client->server->flags & F_AUTOREADONLY) ||
					expwrite(request.from, buf, len,
						client)) {
				DEBUG("STR" );
				ERROR(client, reply);
				continue;
			}
			SEND(client->net, reply);
			DEBUG("STR");
			continue;
		}
		

		DEBUG("STR");
		if (expread(request.from, buf + sizeof(struct nbd_reply), len, client)) {
			DEBUG("STR");
			ERROR(client, reply);
			continue;
		}

		DEBUG("STR");
		memcpy(buf, &reply, sizeof(struct nbd_reply));
		writeit(client->net, buf, len + sizeof(struct nbd_reply));
		DEBUG("STR");
	}
	return 0;
}