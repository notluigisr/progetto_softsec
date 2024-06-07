static struct nft_table *nft_table_lookup_byhandle(const struct net *net,
						   const struct nlattr *nla,
						   u8 genmask, u32 nlpid)
{
	struct nftables_pernet *nft_net;
	struct nft_table *table;

	nft_net = nft_pernet(net);
	list_for_each_entry(table, &nft_net->tables, list) {
		if (be64_to_cpu(nla_get_be64(nla)) == table->handle &&
		    nft_active_genmask(table, genmask)) {
			if (nft_table_has_owner(table) &&
			    nlpid && table->nlpid != nlpid)
				return ERR_PTR(-EPERM);

			return table;
		}
	}

	return ERR_PTR(-ENOENT);
}