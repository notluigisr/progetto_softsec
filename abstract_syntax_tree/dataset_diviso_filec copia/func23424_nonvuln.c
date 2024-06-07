static void igmp6_group_added(struct ifmcaddr6 *mc)
{
	struct net_device *dev = mc->idev->dev;
	char buf[MAX_ADDR_LEN];

	if (IPV6_ADDR_MC_SCOPE(&mc->mca_addr) <
	    IPV6_ADDR_SCOPE_LINKLOCAL)
		return;

	if (!(mc->mca_flags&MAF_LOADED)) {
		mc->mca_flags |= MAF_LOADED;
		if (ndisc_mc_map(&mc->mca_addr, buf, dev, 0) == 0)
			dev_mc_add(dev, buf);
	}

	if (!(dev->flags & IFF_UP) || (mc->mca_flags & MAF_NOREPORT))
		return;

	if (mld_in_v1_mode(mc->idev)) {
		igmp6_join_group(mc);
		return;
	}
	

	
	if (mc->mca_sfmode == MCAST_EXCLUDE)
		mc->mca_crcount = mc->idev->mc_qrv;

	mld_ifc_event(mc->idev);
}