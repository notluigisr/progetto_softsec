static int mpls_route_del(struct mpls_route_config *cfg,
			  struct netlink_ext_ack *extack)
{
	struct net *net = cfg->rc_nlinfo.nl_net;
	unsigned index;
	int err = -EINVAL;

	index = cfg->rc_label;

	if (!mpls_label_ok(net, &index, extack))
		goto errout;

	mpls_route_update(net, index, NULL, &cfg->rc_nlinfo);

	err = 0;
errout:
	return err;
}