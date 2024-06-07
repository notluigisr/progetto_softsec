static int dn_nl_newaddr(struct sk_buff *skb, struct nlmsghdr *nlh)
{
	struct net *net = sock_net(skb->sk);
	struct nlattr *tb[IFA_MAX+1];
	struct net_device *dev;
	struct dn_dev *dn_db;
	struct ifaddrmsg *ifm;
	struct dn_ifaddr *ifa;
	int err;

	if (!capable(CAP_NET_ADMIN))
		return -EPERM;

	if (!net_eq(net, &init_net))
		return -EINVAL;

	err = nlmsg_parse(nlh, sizeof(*ifm), tb, IFA_MAX, dn_ifa_policy);
	if (err < 0)
		return err;

	if (tb[IFA_LOCAL] == NULL)
		return -EINVAL;

	ifm = nlmsg_data(nlh);
	if ((dev = __dev_get_by_index(&init_net, ifm->ifa_index)) == NULL)
		return -ENODEV;

	if ((dn_db = rtnl_dereference(dev->dn_ptr)) == NULL) {
		dn_db = dn_dev_create(dev, &err);
		if (!dn_db)
			return err;
	}

	if ((ifa = dn_dev_alloc_ifa()) == NULL)
		return -ENOBUFS;

	if (tb[IFA_ADDRESS] == NULL)
		tb[IFA_ADDRESS] = tb[IFA_LOCAL];

	ifa->ifa_local = nla_get_le16(tb[IFA_LOCAL]);
	ifa->ifa_address = nla_get_le16(tb[IFA_ADDRESS]);
	ifa->ifa_flags = tb[IFA_FLAGS] ? nla_get_u32(tb[IFA_FLAGS]) :
					 ifm->ifa_flags;
	ifa->ifa_scope = ifm->ifa_scope;
	ifa->ifa_dev = dn_db;

	if (tb[IFA_LABEL])
		nla_strlcpy(ifa->ifa_label, tb[IFA_LABEL], IFNAMSIZ);
	else
		memcpy(ifa->ifa_label, dev->name, IFNAMSIZ);

	err = dn_dev_insert_ifa(dn_db, ifa);
	if (err)
		dn_dev_free_ifa(ifa);

	return err;
}