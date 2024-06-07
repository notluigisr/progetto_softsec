static inline void dnrmg_receive_user_skb(struct sk_buff *skb)
{
	struct nlmsghdr *nlh = nlmsg_hdr(skb);

	if (nlh->nlmsg_len < sizeof(*nlh) || skb->len < nlh->nlmsg_len)
		return;

	if (!capable(CAP_NET_ADMIN))
		RCV_SKB_FAIL(-EPERM);

	

	RCV_SKB_FAIL(-EINVAL);
}