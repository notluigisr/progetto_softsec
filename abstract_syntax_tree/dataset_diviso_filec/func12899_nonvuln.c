static int bcm_recvmsg(struct socket *sock, struct msghdr *msg, size_t size,
		       int flags)
{
	struct sock *sk = sock->sk;
	struct sk_buff *skb;
	int error = 0;
	int noblock;
	int err;

	noblock =  flags & MSG_DONTWAIT;
	flags   &= ~MSG_DONTWAIT;
	skb = skb_recv_datagram(sk, flags, noblock, &error);
	if (!skb)
		return error;

	if (skb->len < size)
		size = skb->len;

	err = memcpy_to_msg(msg, skb->data, size);
	if (err < 0) {
		skb_free_datagram(sk, skb);
		return err;
	}

	sock_recv_ts_and_drops(msg, sk, skb);

	if (msg->msg_name) {
		__sockaddr_check_size(BCM_MIN_NAMELEN);
		msg->msg_namelen = BCM_MIN_NAMELEN;
		memcpy(msg->msg_name, skb->cb, msg->msg_namelen);
	}

	skb_free_datagram(sk, skb);

	return size;
}