static int ctrl_dumpfamily(struct sk_buff *skb, struct netlink_callback *cb)
{

	int i, n = 0;
	struct genl_family *rt;
	struct net *net = sock_net(skb->sk);
	int chains_to_skip = cb->args[0];
	int fams_to_skip = cb->args[1];

	for (i = chains_to_skip; i < GENL_FAM_TAB_SIZE; i++) {
		n = 0;
		list_for_each_entry(rt, genl_family_chain(i), family_list) {
			if (!rt->netnsok && !net_eq(net, &init_net))
				continue;
			if (++n < fams_to_skip)
				continue;
			if (ctrl_fill_info(rt, NETLINK_CB(cb->skb).portid,
					   cb->nlh->nlmsg_seq, NLM_F_MULTI,
					   skb, CTRL_CMD_NEWFAMILY) < 0)
				goto errout;
		}

		fams_to_skip = 0;
	}

errout:
	cb->args[0] = i;
	cb->args[1] = n;

	return skb->len;
}