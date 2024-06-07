static void audit_receive_skb(struct sk_buff *skb)
{
	struct nlmsghdr *nlh;
	
	int len;
	int err;

	nlh = nlmsg_hdr(skb);
	len = skb->len;

	while (nlmsg_ok(nlh, len)) {
		err = audit_receive_msg(skb, nlh);
		
		if (err || (nlh->nlmsg_flags & NLM_F_ACK))
			netlink_ack(skb, nlh, err);

		nlh = nlmsg_next(nlh, &len);
	}
}