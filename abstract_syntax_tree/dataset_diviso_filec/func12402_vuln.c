static void l2cap_sock_teardown_cb(struct l2cap_chan *chan, int err)
{
	struct sock *sk = chan->data;
	struct sock *parent;

	BT_DBG("STR", chan, state_to_string(chan->state));

	
	lock_sock_nested(sk, atomic_read(&chan->nesting));

	parent = bt_sk(sk)->parent;

	switch (chan->state) {
	case BT_OPEN:
	case BT_BOUND:
	case BT_CLOSED:
		break;
	case BT_LISTEN:
		l2cap_sock_cleanup_listen(sk);
		sk->sk_state = BT_CLOSED;
		chan->state = BT_CLOSED;

		break;
	default:
		sk->sk_state = BT_CLOSED;
		chan->state = BT_CLOSED;

		sk->sk_err = err;

		if (parent) {
			bt_accept_unlink(sk);
			parent->sk_data_ready(parent);
		} else {
			sk->sk_state_change(sk);
		}

		break;
	}
	release_sock(sk);

	
	sock_set_flag(sk, SOCK_ZAPPED);

}