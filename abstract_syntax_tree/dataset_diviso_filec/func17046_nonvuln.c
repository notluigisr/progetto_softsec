static int nf_tables_getset(struct sk_buff *skb, const struct nfnl_info *info,
			    const struct nlattr * const nla[])
{
	struct netlink_ext_ack *extack = info->extack;
	u8 genmask = nft_genmask_cur(info->net);
	u8 family = info->nfmsg->nfgen_family;
	struct nft_table *table = NULL;
	struct net *net = info->net;
	const struct nft_set *set;
	struct sk_buff *skb2;
	struct nft_ctx ctx;
	int err;

	if (nla[NFTA_SET_TABLE]) {
		table = nft_table_lookup(net, nla[NFTA_SET_TABLE], family,
					 genmask, 0);
		if (IS_ERR(table)) {
			NL_SET_BAD_ATTR(extack, nla[NFTA_SET_TABLE]);
			return PTR_ERR(table);
		}
	}

	nft_ctx_init(&ctx, net, skb, info->nlh, family, table, NULL, nla);

	if (info->nlh->nlmsg_flags & NLM_F_DUMP) {
		struct netlink_dump_control c = {
			.start = nf_tables_dump_sets_start,
			.dump = nf_tables_dump_sets,
			.done = nf_tables_dump_sets_done,
			.data = &ctx,
			.module = THIS_MODULE,
		};

		return nft_netlink_dump_start_rcu(info->sk, skb, info->nlh, &c);
	}

	
	if (info->nfmsg->nfgen_family == NFPROTO_UNSPEC)
		return -EAFNOSUPPORT;
	if (!nla[NFTA_SET_TABLE])
		return -EINVAL;

	set = nft_set_lookup(table, nla[NFTA_SET_NAME], genmask);
	if (IS_ERR(set))
		return PTR_ERR(set);

	skb2 = alloc_skb(NLMSG_GOODSIZE, GFP_ATOMIC);
	if (skb2 == NULL)
		return -ENOMEM;

	err = nf_tables_fill_set(skb2, &ctx, set, NFT_MSG_NEWSET, 0);
	if (err < 0)
		goto err_fill_set_info;

	return nfnetlink_unicast(skb2, net, NETLINK_CB(skb).portid);

err_fill_set_info:
	kfree_skb(skb2);
	return err;
}