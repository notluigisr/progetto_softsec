static void rds_conn_reset(struct rds_connection *conn)
{
	rdsdebug("STR",
	  &conn->c_laddr, &conn->c_faddr);

	rds_stats_inc(s_conn_reset);
	rds_send_reset(conn);
	conn->c_flags = 0;

	
}