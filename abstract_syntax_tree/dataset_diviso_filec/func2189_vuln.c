static inline int __udp_lib_lport_inuse(__u16 num, struct hlist_head udptable[])
{
	struct sock *sk;
	struct hlist_node *node;

	sk_for_each(sk, node, &udptable[num & (UDP_HTABLE_SIZE - 1)])
		if (sk->sk_hash == num)
			return 1;
	return 0;
}