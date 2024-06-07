static void nfnetlink_rcv(struct sk_buff *skb)
{
	struct nlmsghdr *nlh = nlmsg_hdr(skb);
	struct net *net = sock_net(skb->sk);
	int msglen;

	if (nlh->nlmsg_len < NLMSG_HDRLEN ||
	    skb->len < nlh->nlmsg_len)
		return;

	if (!ns_capable(net->user_ns, CAP_NET_ADMIN)) {
		netlink_ack(skb, nlh, -EPERM);
		return;
	}

	if (nlh->nlmsg_type == NFNL_MSG_BATCH_BEGIN) {
		struct nfgenmsg *nfgenmsg;

		msglen = NLMSG_ALIGN(nlh->nlmsg_len);
		if (msglen > skb->len)
			msglen = skb->len;

		if (nlh->nlmsg_len < NLMSG_HDRLEN ||
		    skb->len < NLMSG_HDRLEN + sizeof(struct nfgenmsg))
			return;

		nfgenmsg = nlmsg_data(nlh);
		skb_pull(skb, msglen);
		nfnetlink_rcv_batch(skb, nlh, nfgenmsg->res_id);
	} else {
		netlink_rcv_skb(skb, &nfnetlink_rcv_msg);
	}
}