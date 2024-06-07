void dn_dev_down(struct net_device *dev)
{
	struct dn_dev *dn_db = rtnl_dereference(dev->dn_ptr);
	struct dn_ifaddr *ifa;

	if (dn_db == NULL)
		return;

	while ((ifa = rtnl_dereference(dn_db->ifa_list)) != NULL) {
		dn_dev_del_ifa(dn_db, &dn_db->ifa_list, 0);
		dn_dev_free_ifa(ifa);
	}

	dn_dev_delete(dev);
}