static ssize_t o2nm_node_num_store(struct config_item *item, const char *page,
				   size_t count)
{
	struct o2nm_node *node = to_o2nm_node(item);
	struct o2nm_cluster *cluster = to_o2nm_cluster_from_node(node);
	unsigned long tmp;
	char *p = (char *)page;
	int ret = 0;

	tmp = simple_strtoul(p, &p, 0);
	if (!p || (*p && (*p != '\n')))
		return -EINVAL;

	if (tmp >= O2NM_MAX_NODES)
		return -ERANGE;

	
	if (!test_bit(O2NM_NODE_ATTR_ADDRESS, &node->nd_set_attributes) ||
	    !test_bit(O2NM_NODE_ATTR_PORT, &node->nd_set_attributes))
		return -EINVAL; 

	write_lock(&cluster->cl_nodes_lock);
	if (cluster->cl_nodes[tmp])
		ret = -EEXIST;
	else if (test_and_set_bit(O2NM_NODE_ATTR_NUM,
			&node->nd_set_attributes))
		ret = -EBUSY;
	else  {
		cluster->cl_nodes[tmp] = node;
		node->nd_num = tmp;
		set_bit(tmp, cluster->cl_nodes_bitmap);
	}
	write_unlock(&cluster->cl_nodes_lock);
	if (ret)
		return ret;

	return count;
}