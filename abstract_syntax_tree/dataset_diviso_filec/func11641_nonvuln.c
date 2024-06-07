void iscsi_requeue_task(struct iscsi_task *task)
{
	struct iscsi_conn *conn = task->conn;

	
	spin_lock_bh(&conn->session->frwd_lock);
	if (list_empty(&task->running)) {
		list_add_tail(&task->running, &conn->requeue);
	} else {
		
		iscsi_put_task(task);
	}
	iscsi_conn_queue_work(conn);
	spin_unlock_bh(&conn->session->frwd_lock);
}