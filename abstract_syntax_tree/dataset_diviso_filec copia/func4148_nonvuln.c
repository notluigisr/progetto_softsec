unsigned int dn_mss_from_pmtu(struct net_device *dev, int mtu)
{
	unsigned int mss = 230 - DN_MAX_NSP_DATA_HEADER;
	if (dev) {
		struct dn_dev *dn_db = rcu_dereference_raw(dev->dn_ptr);
		mtu -= LL_RESERVED_SPACE(dev);
		if (dn_db->use_long)
			mtu -= 21;
		else
			mtu -= 6;
		mtu -= DN_MAX_NSP_DATA_HEADER;
	} else {
		
		mtu -= (21 + DN_MAX_NSP_DATA_HEADER + 16);
	}
	if (mtu > mss)
		mss = mtu;
	return mss;
}