static unsigned int _db_node_put(struct db_arg_chain_tree **node)
{
	if ((*node)->refcnt == 1)
		return _db_tree_put(node);
	(*node)->refcnt--;
	return 0;
}