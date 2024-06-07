smtp_server_connection_create_from_streams(
	struct smtp_server *server,
	struct istream *input, struct ostream *output,
	const struct ip_addr *remote_ip, in_port_t remote_port,
	const struct smtp_server_settings *set,
	const struct smtp_server_callbacks *callbacks, void *context)
{
	struct smtp_server_connection *conn;
	struct event *conn_event;
	int fd_in, fd_out;

	fd_in = i_stream_get_fd(input);
	fd_out = o_stream_get_fd(output);
	i_assert(fd_in >= 0);
	i_assert(fd_out >= 0);

	conn = smtp_server_connection_alloc(server, set, fd_in, fd_out,
					    callbacks, context);
	if (remote_ip != NULL && remote_ip->family != 0)
		conn->conn.remote_ip = *remote_ip;
	if (remote_port != 0)
		conn->conn.remote_port = remote_port;
	conn_event = smtp_server_connection_event_create(server, set);
	conn->conn.event_parent = conn_event;
	connection_init_from_streams(server->conn_list,	&conn->conn, NULL,
				     input, output);
	conn->created_from_streams = TRUE;
	conn->event = conn->conn.event;
	event_unref(&conn_event);

	
	smtp_server_connection_halt(conn);

	e_debug(conn->event, "STR");

	return conn;
}