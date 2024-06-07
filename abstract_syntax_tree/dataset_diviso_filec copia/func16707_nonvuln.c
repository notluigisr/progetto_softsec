static void sco_conn_del(struct hci_conn *hcon, int err)
{
	struct sco_conn *conn = hcon->sco_data;
	struct sock *sk;

	if (!conn)
		return;

	BT_DBG("STR", hcon, conn, err);

	
	sco_conn_lock(conn);
	sk = conn->sk;
	sco_conn_unlock(conn);

	if (sk) {
		sock_hold(sk);
		lock_sock(sk);
		sco_sock_clear_timer(sk);
		sco_chan_del(sk, err);
		release_sock(sk);
		sock_put(sk);

		
		cancel_delayed_work_sync(&conn->timeout_work);
	}

	hcon->sco_data = NULL;
	kfree(conn);
}