void ip_mc_rejoin_groups(struct in_device *in_dev)
{
#ifdef CONFIG_IP_MULTICAST
	struct ip_mc_list *im;
	int type;

	for_each_pmc_rcu(in_dev, im) {
		if (im->multiaddr == IGMP_ALL_HOSTS)
			continue;

		
		if (IGMP_V1_SEEN(in_dev))
			type = IGMP_HOST_MEMBERSHIP_REPORT;
		else if (IGMP_V2_SEEN(in_dev))
			type = IGMPV2_HOST_MEMBERSHIP_REPORT;
		else
			type = IGMPV3_HOST_MEMBERSHIP_REPORT;
		igmp_send_report(in_dev, im, type);
	}
#endif
}