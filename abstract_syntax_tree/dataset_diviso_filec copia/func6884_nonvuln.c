static void __dp_destroy(struct datapath *dp)
{
	int i;

	for (i = 0; i < DP_VPORT_HASH_BUCKETS; i++) {
		struct vport *vport;
		struct hlist_node *n;

		hlist_for_each_entry_safe(vport, n, &dp->ports[i], dp_hash_node)
			if (vport->port_no != OVSP_LOCAL)
				ovs_dp_detach_port(vport);
	}

	list_del_rcu(&dp->list_node);

	
	ovs_dp_detach_port(ovs_vport_ovsl(dp, OVSP_LOCAL));

	
	ovs_flow_tbl_destroy(&dp->table, true);

	call_rcu(&dp->rcu, destroy_dp_rcu);
}