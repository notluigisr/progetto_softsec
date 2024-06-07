static int _server_handle_g(libgdbr_t *g, int (*cmd_cb) (void*, const char*, char*, size_t), void *core_ptr) {
	char *buf;
	
	int buf_len = 4096;
	int ret;
	if (send_ack (g) < 0) {
		return -1;
	}
	if (!(buf = malloc (buf_len))) {
		send_msg (g, "STR");
		return -1;
	}
	memset (buf, 0, buf_len);
	if ((buf_len = cmd_cb (core_ptr, "STR", buf, buf_len)) < 0) {
		free (buf);
		send_msg (g, "STR");
		return -1;
	}
	ret = send_msg (g, buf);
	free (buf);
	return ret;
}