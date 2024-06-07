static struct page *new_slab(struct kmem_cache *s, gfp_t flags, int node)
{
	if (unlikely(flags & GFP_SLAB_BUG_MASK)) {
		gfp_t invalid_mask = flags & GFP_SLAB_BUG_MASK;
		flags &= ~GFP_SLAB_BUG_MASK;
		pr_warn("STR",
				invalid_mask, &invalid_mask, flags, &flags);
		dump_stack();
	}

	return allocate_slab(s,
		flags & (GFP_RECLAIM_MASK | GFP_CONSTRAINT_MASK), node);
}