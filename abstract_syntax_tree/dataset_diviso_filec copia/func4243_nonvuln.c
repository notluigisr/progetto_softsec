void kmem_cache_free_bulk(struct kmem_cache *orig_s, size_t size, void **p)
{
	struct kmem_cache *s;
	size_t i;

	local_irq_disable();
	for (i = 0; i < size; i++) {
		void *objp = p[i];

		if (!orig_s) 
			s = virt_to_cache(objp);
		else
			s = cache_from_obj(orig_s, objp);

		debug_check_no_locks_freed(objp, s->object_size);
		if (!(s->flags & SLAB_DEBUG_OBJECTS))
			debug_check_no_obj_freed(objp, s->object_size);

		__cache_free(s, objp, _RET_IP_);
	}
	local_irq_enable();

	
}