static int sdma_rb_insert(void *arg, struct mmu_rb_node *mnode)
{
	struct sdma_mmu_node *node =
		container_of(mnode, struct sdma_mmu_node, rb);

	atomic_inc(&node->refcount);
	return 0;
}