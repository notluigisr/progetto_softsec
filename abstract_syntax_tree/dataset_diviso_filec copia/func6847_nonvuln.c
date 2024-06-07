static int validate_linkmsg(struct net_device *dev, struct nlattr *tb[])
{
	if (dev) {
		if (tb[IFLA_ADDRESS] &&
		    nla_len(tb[IFLA_ADDRESS]) < dev->addr_len)
			return -EINVAL;

		if (tb[IFLA_BROADCAST] &&
		    nla_len(tb[IFLA_BROADCAST]) < dev->addr_len)
			return -EINVAL;
	}

	if (tb[IFLA_AF_SPEC]) {
		struct nlattr *af;
		int rem, err;

		nla_for_each_nested(af, tb[IFLA_AF_SPEC], rem) {
			const struct rtnl_af_ops *af_ops;

			rcu_read_lock();
			af_ops = rtnl_af_lookup(nla_type(af));
			if (!af_ops) {
				rcu_read_unlock();
				return -EAFNOSUPPORT;
			}

			if (!af_ops->set_link_af) {
				rcu_read_unlock();
				return -EOPNOTSUPP;
			}

			if (af_ops->validate_link_af) {
				err = af_ops->validate_link_af(dev, af);
				if (err < 0) {
					rcu_read_unlock();
					return err;
				}
			}

			rcu_read_unlock();
		}
	}

	return 0;
}