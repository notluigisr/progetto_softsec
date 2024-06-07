static inline bool hugetlb_register_node(struct node *node)
{
	if (__hugetlb_register_node &&
			node_state(node->dev.id, N_MEMORY)) {
		__hugetlb_register_node(node);
		return true;
	}
	return false;
}