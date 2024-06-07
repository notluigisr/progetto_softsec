int ixgbe_ndo_get_vf_config(struct net_device *netdev,
			    int vf, struct ifla_vf_info *ivi)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);
	if (vf >= adapter->num_vfs)
		return -EINVAL;
	ivi->vf = vf;
	memcpy(&ivi->mac, adapter->vfinfo[vf].vf_mac_addresses, ETH_ALEN);
	ivi->max_tx_rate = adapter->vfinfo[vf].tx_rate;
	ivi->min_tx_rate = 0;
	ivi->vlan = adapter->vfinfo[vf].pf_vlan;
	ivi->qos = adapter->vfinfo[vf].pf_qos;
	ivi->spoofchk = adapter->vfinfo[vf].spoofchk_enabled;
	ivi->rss_query_en = adapter->vfinfo[vf].rss_query_enabled;
	ivi->trusted = adapter->vfinfo[vf].trusted;
	return 0;
}