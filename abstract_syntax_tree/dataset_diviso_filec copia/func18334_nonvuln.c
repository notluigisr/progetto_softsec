static void geneve_destroy_tunnels(struct net *net, struct list_head *head)
{
	struct geneve_net *gn = net_generic(net, geneve_net_id);
	struct geneve_dev *geneve, *next;
	struct net_device *dev, *aux;

	
	for_each_netdev_safe(net, dev, aux)
		if (dev->rtnl_link_ops == &geneve_link_ops)
			unregister_netdevice_queue(dev, head);

	
	list_for_each_entry_safe(geneve, next, &gn->geneve_list, next) {
		
		if (!net_eq(dev_net(geneve->dev), net))
			unregister_netdevice_queue(geneve->dev, head);
	}

	WARN_ON_ONCE(!list_empty(&gn->sock_list));
}