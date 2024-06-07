 * stop work. But, in that case, it is guaranteed not to race with
 * iscsi_destroy by conn_mutex.
 */
static void iscsi_if_stop_conn(struct iscsi_cls_conn *conn, int flag)
{
	
	mutex_lock(&conn_mutex);
	conn->transport->stop_conn(conn, flag);