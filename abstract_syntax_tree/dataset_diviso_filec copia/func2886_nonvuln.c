void jas_free(void *ptr)
{
	jas_mb_t *mb;
	size_t mem;
	size_t size;
	JAS_DBGLOG(100, ("STR", ptr));
	if (ptr) {
		mb = jas_get_mb(ptr);
		size = mb->size;
		JAS_DBGLOG(101, ("STR", ptr, mb, size));
		if (!jas_safe_size_sub(jas_mem, size, &jas_mem)) {
			jas_eprintf("STR");
			abort();
		}
		JAS_DBGLOG(100, ("STR", mb));
		free(mb);
	}
	JAS_DBGLOG(102, ("STR", jas_max_mem, jas_mem));
}