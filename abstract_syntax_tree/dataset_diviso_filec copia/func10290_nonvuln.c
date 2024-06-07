static netdev_tx_t __bond_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct bonding *bond = netdev_priv(dev);

	if (TX_QUEUE_OVERRIDE(bond->params.mode)) {
		if (!bond_slave_override(bond, skb))
			return NETDEV_TX_OK;
	}

	switch (bond->params.mode) {
	case BOND_MODE_ROUNDROBIN:
		return bond_xmit_roundrobin(skb, dev);
	case BOND_MODE_ACTIVEBACKUP:
		return bond_xmit_activebackup(skb, dev);
	case BOND_MODE_XOR:
		return bond_xmit_xor(skb, dev);
	case BOND_MODE_BROADCAST:
		return bond_xmit_broadcast(skb, dev);
	case BOND_MODE_8023AD:
		return bond_3ad_xmit_xor(skb, dev);
	case BOND_MODE_ALB:
	case BOND_MODE_TLB:
		return bond_alb_xmit(skb, dev);
	default:
		
		pr_err("STR",
		       dev->name, bond->params.mode);
		WARN_ON_ONCE(1);
		dev_kfree_skb(skb);
		return NETDEV_TX_OK;
	}
}