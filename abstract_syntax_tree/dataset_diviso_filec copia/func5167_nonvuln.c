
void skb_complete_tx_timestamp(struct sk_buff *skb,
			       struct skb_shared_hwtstamps *hwtstamps)
{
	struct sock *sk = skb->sk;

	if (!skb_may_tx_timestamp(sk, false))
		goto err;

	
	if (likely(refcount_inc_not_zero(&sk->sk_refcnt))) {
		*skb_hwtstamps(skb) = *hwtstamps;
		__skb_complete_tx_timestamp(skb, sk, SCM_TSTAMP_SND, false);
		sock_put(sk);
		return;
	}

err:
	kfree_skb(skb);