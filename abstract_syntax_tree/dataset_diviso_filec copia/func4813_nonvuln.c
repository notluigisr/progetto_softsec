void node_set_perf_attrs(unsigned int nid, struct node_hmem_attrs *hmem_attrs,
			 unsigned access)
{
	struct node_access_nodes *c;
	struct node *node;
	int i;

	if (WARN_ON_ONCE(!node_online(nid)))
		return;

	node = node_devices[nid];
	c = node_init_node_access(node, access);
	if (!c)
		return;

	c->hmem_attrs = *hmem_attrs;
	for (i = 0; access_attrs[i] != NULL; i++) {
		if (sysfs_add_file_to_group(&c->dev.kobj, access_attrs[i],
					    "STR")) {
			pr_info("STR",
				nid);
			break;
		}
	}
}