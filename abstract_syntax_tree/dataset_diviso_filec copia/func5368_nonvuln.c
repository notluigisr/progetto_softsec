static int tcp_peek_sndq(struct sock *sk, struct msghdr *msg, int len)
{
	struct sk_buff *skb;
	int copied = 0, err = 0;

	

	skb_rbtree_walk(skb, &sk->tcp_rtx_queue) {
		err = skb_copy_datagram_msg(skb, 0, msg, skb->len);
		if (err)
			return err;
		copied += skb->len;
	}

	skb_queue_walk(&sk->sk_write_queue, skb) {
		err = skb_copy_datagram_msg(skb, 0, msg, skb->len);
		if (err)
			break;

		copied += skb->len;
	}

	return err ?: copied;
}