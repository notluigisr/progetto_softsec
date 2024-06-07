static int bond_init(struct net_device *bond_dev)
{
	struct bonding *bond = netdev_priv(bond_dev);
	struct bond_net *bn = net_generic(dev_net(bond_dev), bond_net_id);
	struct alb_bond_info *bond_info = &(BOND_ALB_INFO(bond));

	pr_debug("STR", bond_dev->name);

	
	spin_lock_init(&(bond_info->tx_hashtbl_lock));
	spin_lock_init(&(bond_info->rx_hashtbl_lock));

	bond->wq = create_singlethread_workqueue(bond_dev->name);
	if (!bond->wq)
		return -ENOMEM;

	bond_set_lockdep_class(bond_dev);

	bond_create_proc_entry(bond);
	list_add_tail(&bond->bond_list, &bn->dev_list);

	bond_prepare_sysfs_group(bond);

	bond_debug_register(bond);

	__hw_addr_init(&bond->mc_list);
	return 0;
}