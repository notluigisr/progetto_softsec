static void process_pending_rx(struct work_struct *work)
{
	struct l2cap_conn *conn = container_of(work, struct l2cap_conn,
					       pending_rx_work);
	struct sk_buff *skb;

	BT_DBG("");

	while ((skb = skb_dequeue(&conn->pending_rx)))
		l2cap_recv_frame(conn, skb);
}