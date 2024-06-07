static void sctp_generate_timeout_event(struct sctp_association *asoc,
					sctp_event_timeout_t timeout_type)
{
	struct net *net = sock_net(asoc->base.sk);
	int error = 0;

	bh_lock_sock(asoc->base.sk);
	if (sock_owned_by_user(asoc->base.sk)) {
		pr_debug("STR", __func__,
			 timeout_type);

		
		if (!mod_timer(&asoc->timers[timeout_type], jiffies + (HZ/20)))
			sctp_association_hold(asoc);
		goto out_unlock;
	}

	
	if (asoc->base.dead)
		goto out_unlock;

	
	error = sctp_do_sm(net, SCTP_EVENT_T_TIMEOUT,
			   SCTP_ST_TIMEOUT(timeout_type),
			   asoc->state, asoc->ep, asoc,
			   (void *)timeout_type, GFP_ATOMIC);

	if (error)
		asoc->base.sk->sk_err = -error;

out_unlock:
	bh_unlock_sock(asoc->base.sk);
	sctp_association_put(asoc);
}