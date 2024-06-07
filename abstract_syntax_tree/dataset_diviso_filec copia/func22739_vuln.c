int dccp_sendmsg(struct sock *sk, struct msghdr *msg, size_t len)
{
	const struct dccp_sock *dp = dccp_sk(sk);
	const int flags = msg->msg_flags;
	const int noblock = flags & MSG_DONTWAIT;
	struct sk_buff *skb;
	int rc, size;
	long timeo;

	trace_dccp_probe(sk, len);

	if (len > dp->dccps_mss_cache)
		return -EMSGSIZE;

	lock_sock(sk);

	if (dccp_qpolicy_full(sk)) {
		rc = -EAGAIN;
		goto out_release;
	}

	timeo = sock_sndtimeo(sk, noblock);

	
	
	if ((1 << sk->sk_state) & ~(DCCPF_OPEN | DCCPF_PARTOPEN))
		if ((rc = sk_stream_wait_connect(sk, &timeo)) != 0)
			goto out_release;

	size = sk->sk_prot->max_header + len;
	release_sock(sk);
	skb = sock_alloc_send_skb(sk, size, noblock, &rc);
	lock_sock(sk);
	if (skb == NULL)
		goto out_release;

	skb_reserve(skb, sk->sk_prot->max_header);
	rc = memcpy_from_msg(skb_put(skb, len), msg, len);
	if (rc != 0)
		goto out_discard;

	rc = dccp_msghdr_parse(msg, skb);
	if (rc != 0)
		goto out_discard;

	dccp_qpolicy_push(sk, skb);
	
	if (!timer_pending(&dp->dccps_xmit_timer))
		dccp_write_xmit(sk);
out_release:
	release_sock(sk);
	return rc ? : len;
out_discard:
	kfree_skb(skb);
	goto out_release;
}