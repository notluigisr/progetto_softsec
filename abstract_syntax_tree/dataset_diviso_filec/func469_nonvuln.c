void tcp_wfree(struct sk_buff *skb)
{
	struct sock *sk = skb->sk;
	struct tcp_sock *tp = tcp_sk(sk);
	unsigned long flags, nval, oval;

	
	WARN_ON(refcount_sub_and_test(skb->truesize - 1, &sk->sk_wmem_alloc));

	
	if (refcount_read(&sk->sk_wmem_alloc) >= SKB_TRUESIZE(1) && this_cpu_ksoftirqd() == current)
		goto out;

	for (oval = READ_ONCE(sk->sk_tsq_flags);; oval = nval) {
		struct tsq_tasklet *tsq;
		bool empty;

		if (!(oval & TSQF_THROTTLED) || (oval & TSQF_QUEUED))
			goto out;

		nval = (oval & ~TSQF_THROTTLED) | TSQF_QUEUED | TCPF_TSQ_DEFERRED;
		nval = cmpxchg(&sk->sk_tsq_flags, oval, nval);
		if (nval != oval)
			continue;

		
		local_irq_save(flags);
		tsq = this_cpu_ptr(&tsq_tasklet);
		empty = list_empty(&tsq->head);
		list_add(&tp->tsq_node, &tsq->head);
		if (empty)
			tasklet_schedule(&tsq->tasklet);
		local_irq_restore(flags);
		return;
	}
out:
	sk_free(sk);
}