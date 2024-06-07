static int cgw_remove_job(struct sk_buff *skb, struct nlmsghdr *nlh)
{
	struct cgw_job *gwj = NULL;
	struct hlist_node *nx;
	struct rtcanmsg *r;
	struct cf_mod mod;
	struct can_can_gw ccgw;
	u8 limhops = 0;
	int err = 0;

	if (!capable(CAP_NET_ADMIN))
		return -EPERM;

	if (nlmsg_len(nlh) < sizeof(*r))
		return -EINVAL;

	r = nlmsg_data(nlh);
	if (r->can_family != AF_CAN)
		return -EPFNOSUPPORT;

	
	if (r->gwtype != CGW_TYPE_CAN_CAN)
		return -EINVAL;

	err = cgw_parse_attr(nlh, &mod, CGW_TYPE_CAN_CAN, &ccgw, &limhops);
	if (err < 0)
		return err;

	
	if (!ccgw.src_idx && !ccgw.dst_idx) {
		cgw_remove_all_jobs();
		return 0;
	}

	err = -EINVAL;

	ASSERT_RTNL();

	
	hlist_for_each_entry_safe(gwj, nx, &cgw_list, list) {

		if (gwj->flags != r->flags)
			continue;

		if (gwj->limit_hops != limhops)
			continue;

		if (memcmp(&gwj->mod, &mod, sizeof(mod)))
			continue;

		
		if (memcmp(&gwj->ccgw, &ccgw, sizeof(ccgw)))
			continue;

		hlist_del(&gwj->list);
		cgw_unregister_filter(gwj);
		kmem_cache_free(cgw_cache, gwj);
		err = 0;
		break;
	}

	return err;
}