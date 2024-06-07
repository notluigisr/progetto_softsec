int macvlan_common_newlink(struct net *src_net, struct net_device *dev,
			   struct nlattr *tb[], struct nlattr *data[],
			   int (*receive)(struct sk_buff *skb),
			   int (*forward)(struct net_device *dev,
					  struct sk_buff *skb))
{
	struct macvlan_dev *vlan = netdev_priv(dev);
	struct macvlan_port *port;
	struct net_device *lowerdev;
	int err;

	if (!tb[IFLA_LINK])
		return -EINVAL;

	lowerdev = __dev_get_by_index(src_net, nla_get_u32(tb[IFLA_LINK]));
	if (lowerdev == NULL)
		return -ENODEV;

	
	if (lowerdev->rtnl_link_ops == dev->rtnl_link_ops) {
		struct macvlan_dev *lowervlan = netdev_priv(lowerdev);
		lowerdev = lowervlan->lowerdev;
	}

	if (!tb[IFLA_MTU])
		dev->mtu = lowerdev->mtu;
	else if (dev->mtu > lowerdev->mtu)
		return -EINVAL;

	if (!tb[IFLA_ADDRESS])
		random_ether_addr(dev->dev_addr);

	if (!macvlan_port_exists(lowerdev)) {
		err = macvlan_port_create(lowerdev);
		if (err < 0)
			return err;
	}
	port = macvlan_port_get(lowerdev);

	
	if (port->passthru)
		return -EINVAL;

	vlan->lowerdev = lowerdev;
	vlan->dev      = dev;
	vlan->port     = port;
	vlan->receive  = receive;
	vlan->forward  = forward;

	vlan->mode     = MACVLAN_MODE_VEPA;
	if (data && data[IFLA_MACVLAN_MODE])
		vlan->mode = nla_get_u32(data[IFLA_MACVLAN_MODE]);

	if (vlan->mode == MACVLAN_MODE_PASSTHRU) {
		if (port->count)
			return -EINVAL;
		port->passthru = true;
		memcpy(dev->dev_addr, lowerdev->dev_addr, ETH_ALEN);
	}

	port->count += 1;
	err = register_netdevice(dev);
	if (err < 0)
		goto destroy_port;

	list_add_tail(&vlan->list, &port->vlans);
	netif_stacked_transfer_operstate(lowerdev, dev);

	return 0;

destroy_port:
	port->count -= 1;
	if (!port->count)
		macvlan_port_destroy(lowerdev);

	return err;
}