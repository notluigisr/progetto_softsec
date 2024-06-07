static void l2cap_chan_timeout(struct work_struct *work)
{
	struct l2cap_chan *chan = container_of(work, struct l2cap_chan,
					       chan_timer.work);
	struct l2cap_conn *conn = chan->conn;
	int reason;

	BT_DBG("STR", chan, state_to_string(chan->state));

	mutex_lock(&conn->chan_lock);
	l2cap_chan_lock(chan);

	if (chan->state == BT_CONNECTED || chan->state == BT_CONFIG)
		reason = ECONNREFUSED;
	else if (chan->state == BT_CONNECT &&
		 chan->sec_level != BT_SECURITY_SDP)
		reason = ECONNREFUSED;
	else
		reason = ETIMEDOUT;

	l2cap_chan_close(chan, reason);

	l2cap_chan_unlock(chan);

	chan->ops->close(chan);
	mutex_unlock(&conn->chan_lock);

	l2cap_chan_put(chan);
}