static int __udpv6_queue_rcv_skb(struct sock *sk, struct sk_buff *skb)
{
	int rc;

	if (!ipv6_addr_any(&sk->sk_v6_daddr)) {
		sock_rps_save_rxhash(sk, skb);
		sk_mark_napi_id(sk, skb);
		sk_incoming_cpu_update(sk);
	}

	rc = __sock_queue_rcv_skb(sk, skb);
	if (rc < 0) {
		int is_udplite = IS_UDPLITE(sk);

		
		if (rc == -ENOMEM)
			UDP6_INC_STATS(sock_net(sk),
					 UDP_MIB_RCVBUFERRORS, is_udplite);
		UDP6_INC_STATS(sock_net(sk), UDP_MIB_INERRORS, is_udplite);
		kfree_skb(skb);
		return -1;
	}
	return 0;
}