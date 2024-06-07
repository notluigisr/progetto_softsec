nfp_abm_u32_knode_replace(struct nfp_abm_link *alink,
			  struct tc_cls_u32_knode *knode,
			  __be16 proto, struct netlink_ext_ack *extack)
{
	struct nfp_abm_u32_match *match = NULL, *iter;
	unsigned int tos_off;
	u8 mask, val;
	int err;

	if (!nfp_abm_u32_check_knode(alink->abm, knode, proto, extack))
		goto err_delete;

	tos_off = proto == htons(ETH_P_IP) ? 16 : 20;

	
	val = be32_to_cpu(knode->sel->keys[0].val) >> tos_off & 0xff;
	mask = be32_to_cpu(knode->sel->keys[0].mask) >> tos_off & 0xff;

	
	list_for_each_entry(iter, &alink->dscp_map, list) {
		u32 cmask;

		if (iter->handle == knode->handle) {
			match = iter;
			continue;
		}

		cmask = iter->mask & mask;
		if ((iter->val & cmask) == (val & cmask) &&
		    iter->band != knode->res->classid) {
			NL_SET_ERR_MSG_MOD(extack, "STR");
			goto err_delete;
		}
	}

	if (!match) {
		match = kzalloc(sizeof(*match), GFP_KERNEL);
		if (!match)
			return -ENOMEM;
		list_add(&match->list, &alink->dscp_map);
	}
	match->handle = knode->handle;
	match->band = knode->res->classid;
	match->mask = mask;
	match->val = val;

	err = nfp_abm_update_band_map(alink);
	if (err)
		goto err_delete;

	return 0;

err_delete:
	nfp_abm_u32_knode_delete(alink, knode);
	return -EOPNOTSUPP;
}