static int tc_ctl_action(struct sk_buff *skb, struct nlmsghdr *n)
{
	struct net *net = sock_net(skb->sk);
	struct nlattr *tca[TCA_ACT_MAX + 1];
	u32 portid = skb ? NETLINK_CB(skb).portid : 0;
	int ret = 0, ovr = 0;

	if ((n->nlmsg_type != RTM_GETACTION) && !capable(CAP_NET_ADMIN))
		return -EPERM;

	ret = nlmsg_parse(n, sizeof(struct tcamsg), tca, TCA_ACT_MAX, NULL);
	if (ret < 0)
		return ret;

	if (tca[TCA_ACT_TAB] == NULL) {
		pr_notice("STR");
		return -EINVAL;
	}

	
	switch (n->nlmsg_type) {
	case RTM_NEWACTION:
		
		if (n->nlmsg_flags & NLM_F_REPLACE)
			ovr = 1;
replay:
		ret = tcf_action_add(net, tca[TCA_ACT_TAB], n, portid, ovr);
		if (ret == -EAGAIN)
			goto replay;
		break;
	case RTM_DELACTION:
		ret = tca_action_gd(net, tca[TCA_ACT_TAB], n,
				    portid, RTM_DELACTION);
		break;
	case RTM_GETACTION:
		ret = tca_action_gd(net, tca[TCA_ACT_TAB], n,
				    portid, RTM_GETACTION);
		break;
	default:
		BUG();
	}

	return ret;
}