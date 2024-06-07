int __ipv6_dev_mc_dec(struct inet6_dev *idev, const struct in6_addr *addr)
{
	struct ifmcaddr6 *ma, __rcu **map;

	ASSERT_RTNL();

	mutex_lock(&idev->mc_lock);
	for (map = &idev->mc_list;
	     (ma = mc_dereference(*map, idev));
	     map = &ma->next) {
		if (ipv6_addr_equal(&ma->mca_addr, addr)) {
			if (--ma->mca_users == 0) {
				*map = ma->next;

				igmp6_group_dropped(ma);
				ip6_mc_clear_src(ma);
				mutex_unlock(&idev->mc_lock);

				ma_put(ma);
				return 0;
			}
			mutex_unlock(&idev->mc_lock);
			return 0;
		}
	}

	mutex_unlock(&idev->mc_lock);
	return -ENOENT;
}