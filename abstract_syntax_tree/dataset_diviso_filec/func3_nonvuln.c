void smtp_server_connection_timeout_start(struct smtp_server_connection *conn)
{
	if (conn->disconnected)
		return;

	if (conn->to_idle == NULL &&
		conn->set.max_client_idle_time_msecs > 0) {
		e_debug(conn->event, "STR");

		conn->to_idle = timeout_add(
			conn->set.max_client_idle_time_msecs,
			smtp_server_connection_idle_timeout, conn);
	}
}