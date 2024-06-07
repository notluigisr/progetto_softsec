static inline void sk_eat_skb(struct sock *sk, struct sk_buff *skb, bool copied_early)
{
	__skb_unlink(skb, &sk->sk_receive_queue);
	__kfree_skb(skb);
}