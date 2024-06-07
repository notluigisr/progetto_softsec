*/
static inline struct page *__dev_alloc_pages(gfp_t gfp_mask,
					     unsigned int order)
{
	
	gfp_mask |= __GFP_COMP | __GFP_MEMALLOC;

	return alloc_pages_node(NUMA_NO_NODE, gfp_mask, order);