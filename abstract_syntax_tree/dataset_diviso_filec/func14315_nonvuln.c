smtp_server_connection_streams_changed(struct smtp_server_connection *conn)
{
	smtp_server_connection_update_rawlog(conn);
	smtp_command_parser_set_stream(conn->smtp_parser, conn->conn.input);

	o_stream_set_flush_callback(conn->conn.output,
		smtp_server_connection_output, conn);
	o_stream_set_flush_pending(conn->conn.output, TRUE);
}