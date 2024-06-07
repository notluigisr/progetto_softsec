void tcp_v4_destroy_sock(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);

	tcp_clear_xmit_timers(sk);

	tcp_cleanup_congestion_control(sk);

	
	tcp_write_queue_purge(sk);

	
	__skb_queue_purge(&tp->out_of_order_queue);

#ifdef CONFIG_TCP_MD5SIG
	
	if (tp->md5sig_info) {
		tcp_clear_md5_list(sk);
		kfree_rcu(tp->md5sig_info, rcu);
		tp->md5sig_info = NULL;
	}
#endif

#ifdef CONFIG_NET_DMA
	
	__skb_queue_purge(&sk->sk_async_wait_queue);
#endif

	
	__skb_queue_purge(&tp->ucopy.prequeue);

	
	if (inet_csk(sk)->icsk_bind_hash)
		inet_put_port(sk);

	BUG_ON(tp->fastopen_rsk != NULL);

	
	tcp_free_fastopen_req(tp);

	sk_sockets_allocated_dec(sk);
	sock_release_memcg(sk);
}