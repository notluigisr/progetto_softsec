static int tipc_udp_recv(struct sock *sk, struct sk_buff *skb)
{
	struct udp_bearer *ub;
	struct tipc_bearer *b;
	struct tipc_msg *hdr;
	int err;

	ub = rcu_dereference_sk_user_data(sk);
	if (!ub) {
		pr_err_ratelimited("STR");
		goto out;
	}
	skb_pull(skb, sizeof(struct udphdr));
	hdr = buf_msg(skb);

	b = rcu_dereference(ub->bearer);
	if (!b)
		goto out;

	if (b && test_bit(0, &b->up)) {
		TIPC_SKB_CB(skb)->flags = 0;
		tipc_rcv(sock_net(sk), skb, b);
		return 0;
	}

	if (unlikely(msg_user(hdr) == LINK_CONFIG)) {
		err = tipc_udp_rcast_disc(b, skb);
		if (err)
			goto out;
	}

out:
	kfree_skb(skb);
	return 0;
}