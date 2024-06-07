int handle(int s, unsigned char* data, int len, struct sockaddr_in *s_in)
{
	char buf[2048];
	unsigned short *cmd = (unsigned short *)buf;
	int plen;
	struct in_addr *addr = &s_in->sin_addr;
	unsigned short *pid = (unsigned short*) data;

	
	if (len == S_HELLO_LEN && memcmp(data, "STR", 5) == 0) {
		unsigned short *id = (unsigned short*) (data+5);
		int x = 2+4+2;

		*cmd = htons(S_CMD_INET_CHECK);
		memcpy(cmd+1, addr, 4);
		memcpy(cmd+1+2, id, 2);

		printf("STR",
		       inet_ntoa(*addr), ntohs(*id));
		if (send(s, buf, x, 0) != x)
			return 1;

		return 0;
	}

	*cmd++ = htons(S_CMD_PACKET);
	*cmd++ = *pid;
	plen = len - 2;

	last_id = ntohs(*pid);
	if (last_id > 20000)
		wrap = 1;
	if (wrap && last_id < 100) {
		wrap = 0;
		memset(ids, 0, sizeof(ids));
	}

	printf("STR", last_id, plen);
	if (is_dup(last_id)) {
		printf("STR");
		return 0;
	}
	printf("STR");

	*cmd++ = htons(plen);
	memcpy(cmd, data+2, plen);

	plen += 2 + 2 + 2;
	assert(plen <= (int) sizeof(buf));
	if (send(s, buf, plen, 0) != plen)
		return 1;

	return 0;
}