static inline int select_size(const struct sock *sk, bool sg)
{
	const struct tcp_sock *tp = tcp_sk(sk);
	int tmp = tp->mss_cache;

	if (sg) {
		if (sk_can_gso(sk)) {
			
			tmp = SKB_WITH_OVERHEAD(2048 - MAX_TCP_HEADER);
		} else {
			int pgbreak = SKB_MAX_HEAD(MAX_TCP_HEADER);

			if (tmp >= pgbreak &&
			    tmp <= pgbreak + (MAX_SKB_FRAGS - 1) * PAGE_SIZE)
				tmp = pgbreak;
		}
	}

	return tmp;
}