static void tipc_node_link_failover(struct tipc_node *n, struct tipc_link *l,
				    struct tipc_link *tnl,
				    struct sk_buff_head *xmitq)
{
	
	if (!tipc_link_is_up(tnl))
		return;

	
	if (l && !tipc_link_is_reset(l))
		return;

	tipc_link_fsm_evt(tnl, LINK_SYNCH_END_EVT);
	tipc_node_fsm_evt(n, NODE_SYNCH_END_EVT);

	n->sync_point = tipc_link_rcv_nxt(tnl) + (U16_MAX / 2 - 1);
	tipc_link_failover_prepare(l, tnl, xmitq);

	if (l)
		tipc_link_fsm_evt(l, LINK_FAILOVER_BEGIN_EVT);
	tipc_node_fsm_evt(n, NODE_FAILOVER_BEGIN_EVT);
}