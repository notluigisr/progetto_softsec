static void igmp6_group_queried(struct ifmcaddr6 *ma, unsigned long resptime)
{
	unsigned long delay = resptime;

	
	if (ipv6_addr_is_ll_all_nodes(&ma->mca_addr) ||
	    IPV6_ADDR_MC_SCOPE(&ma->mca_addr) < IPV6_ADDR_SCOPE_LINKLOCAL)
		return;

	if (cancel_delayed_work(&ma->mca_work)) {
		refcount_dec(&ma->mca_refcnt);
		delay = ma->mca_work.timer.expires - jiffies;
	}

	if (delay >= resptime)
		delay = prandom_u32() % resptime;

	if (!mod_delayed_work(mld_wq, &ma->mca_work, delay))
		refcount_inc(&ma->mca_refcnt);
	ma->mca_flags |= MAF_TIMER_RUNNING;
}