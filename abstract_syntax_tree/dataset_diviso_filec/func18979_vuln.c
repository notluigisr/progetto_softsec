int inet6_sk_rebuild_header(struct sock *sk)
{
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct dst_entry *dst;

	dst = __sk_dst_check(sk, np->dst_cookie);

	if (!dst) {
		struct inet_sock *inet = inet_sk(sk);
		struct in6_addr *final_p, final;
		struct flowi6 fl6;

		memset(&fl6, 0, sizeof(fl6));
		fl6.flowi6_proto = sk->sk_protocol;
		fl6.daddr = sk->sk_v6_daddr;
		fl6.saddr = np->saddr;
		fl6.flowlabel = np->flow_label;
		fl6.flowi6_oif = sk->sk_bound_dev_if;
		fl6.flowi6_mark = sk->sk_mark;
		fl6.fl6_dport = inet->inet_dport;
		fl6.fl6_sport = inet->inet_sport;
		security_sk_classify_flow(sk, flowi6_to_flowi(&fl6));

		final_p = fl6_update_dst(&fl6, np->opt, &final);

		dst = ip6_dst_lookup_flow(sk, &fl6, final_p);
		if (IS_ERR(dst)) {
			sk->sk_route_caps = 0;
			sk->sk_err_soft = -PTR_ERR(dst);
			return PTR_ERR(dst);
		}

		__ip6_dst_store(sk, dst, NULL, NULL);
	}

	return 0;
}