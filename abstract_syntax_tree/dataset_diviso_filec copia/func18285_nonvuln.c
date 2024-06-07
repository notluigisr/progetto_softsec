static void fib_magic(int cmd, int type, __le16 dst, int dst_len, struct dn_ifaddr *ifa)
{
	struct dn_fib_table *tb;
	struct {
		struct nlmsghdr nlh;
		struct rtmsg rtm;
	} req;
	struct {
		struct nlattr hdr;
		__le16 dst;
	} dst_attr = {
		.dst = dst,
	};
	struct {
		struct nlattr hdr;
		__le16 prefsrc;
	} prefsrc_attr = {
		.prefsrc = ifa->ifa_local,
	};
	struct {
		struct nlattr hdr;
		u32 oif;
	} oif_attr = {
		.oif = ifa->ifa_dev->dev->ifindex,
	};
	struct nlattr *attrs[RTA_MAX+1] = {
		[RTA_DST] = (struct nlattr *) &dst_attr,
		[RTA_PREFSRC] = (struct nlattr * ) &prefsrc_attr,
		[RTA_OIF] = (struct nlattr *) &oif_attr,
	};

	memset(&req.rtm, 0, sizeof(req.rtm));

	if (type == RTN_UNICAST)
		tb = dn_fib_get_table(RT_MIN_TABLE, 1);
	else
		tb = dn_fib_get_table(RT_TABLE_LOCAL, 1);

	if (tb == NULL)
		return;

	req.nlh.nlmsg_len = sizeof(req);
	req.nlh.nlmsg_type = cmd;
	req.nlh.nlmsg_flags = NLM_F_REQUEST|NLM_F_CREATE|NLM_F_APPEND;
	req.nlh.nlmsg_pid = 0;
	req.nlh.nlmsg_seq = 0;

	req.rtm.rtm_dst_len = dst_len;
	req.rtm.rtm_table = tb->n;
	req.rtm.rtm_protocol = RTPROT_KERNEL;
	req.rtm.rtm_scope = (type != RTN_LOCAL ? RT_SCOPE_LINK : RT_SCOPE_HOST);
	req.rtm.rtm_type = type;

	if (cmd == RTM_NEWROUTE)
		tb->insert(tb, &req.rtm, attrs, &req.nlh, NULL);
	else
		tb->delete(tb, &req.rtm, attrs, &req.nlh, NULL);
}