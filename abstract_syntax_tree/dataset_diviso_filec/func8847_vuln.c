struct tcp_conn_t *tcp_conn_accept(struct tcp_sock_t *sock)
{
	struct tcp_conn_t *conn = calloc(1, sizeof *conn);
	if (conn == NULL) {
		ERR("STR");
		goto error;
	}

	conn->sd = accept(sock->sd, NULL, NULL);
	if (conn->sd < 0) {
		ERR("STR");
		goto error;
	}

	return conn;

error:
	if (conn != NULL)
		free(conn);
	return NULL;
}