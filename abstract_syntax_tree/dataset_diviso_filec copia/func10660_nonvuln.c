static struct kmem_cache_cpu *alloc_kmem_cache_cpu(struct kmem_cache *s,
							int cpu, gfp_t flags)
{
	struct kmem_cache_cpu *c = per_cpu(kmem_cache_cpu_free, cpu);

	if (c)
		per_cpu(kmem_cache_cpu_free, cpu) =
				(void *)c->freelist;
	else {
		
		c = kmalloc_node(
			ALIGN(sizeof(struct kmem_cache_cpu), cache_line_size()),
			flags, cpu_to_node(cpu));
		if (!c)
			return NULL;
	}

	init_kmem_cache_cpu(s, c);
	return c;
}