void br_multicast_open(struct net_bridge *br)
{
	br->multicast_startup_queries_sent = 0;

	if (br->multicast_disabled)
		return;

	mod_timer(&br->multicast_query_timer, jiffies);
}