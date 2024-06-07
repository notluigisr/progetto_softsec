static void sctp_close(struct sock *sk, long timeout)
{
	struct net *net = sock_net(sk);
	struct sctp_endpoint *ep;
	struct sctp_association *asoc;
	struct list_head *pos, *temp;
	unsigned int data_was_unread;

	pr_debug("STR", __func__, sk, timeout);

	lock_sock(sk);
	sk->sk_shutdown = SHUTDOWN_MASK;
	sk->sk_state = SCTP_SS_CLOSING;

	ep = sctp_sk(sk)->ep;

	
	data_was_unread = sctp_queue_purge_ulpevents(&sk->sk_receive_queue);
	data_was_unread += sctp_queue_purge_ulpevents(&sctp_sk(sk)->pd_lobby);

	
	list_for_each_safe(pos, temp, &ep->asocs) {
		asoc = list_entry(pos, struct sctp_association, asocs);

		if (sctp_style(sk, TCP)) {
			
			if (sctp_state(asoc, CLOSED)) {
				sctp_unhash_established(asoc);
				sctp_association_free(asoc);
				continue;
			}
		}

		if (data_was_unread || !skb_queue_empty(&asoc->ulpq.lobby) ||
		    !skb_queue_empty(&asoc->ulpq.reasm) ||
		    (sock_flag(sk, SOCK_LINGER) && !sk->sk_lingertime)) {
			struct sctp_chunk *chunk;

			chunk = sctp_make_abort_user(asoc, NULL, 0);
			if (chunk)
				sctp_primitive_ABORT(net, asoc, chunk);
		} else
			sctp_primitive_SHUTDOWN(net, asoc, NULL);
	}

	
	if (sctp_style(sk, TCP) && timeout)
		sctp_wait_for_close(sk, timeout);

	
	release_sock(sk);

	
	local_bh_disable();
	bh_lock_sock(sk);

	
	sock_hold(sk);
	sk_common_release(sk);

	bh_unlock_sock(sk);
	local_bh_enable();

	sock_put(sk);

	SCTP_DBG_OBJCNT_DEC(sock);
}