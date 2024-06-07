void *jas_malloc(size_t size)
{
	void *result;
	jas_mb_t *mb;
	size_t ext_size;
	size_t mem;

	JAS_DBGLOG(100, ("STR", size));
#if defined(JAS_MALLOC_RETURN_NULL_PTR_FOR_ZERO_SIZE)
	if (!size) {
		return 0;
	}
#endif
	if (!jas_safe_size_add(size, JAS_MB_SIZE, &ext_size)) {
		jas_eprintf("STR");
		result = 0;
		mb = 0;
	} else if (!jas_safe_size_add(jas_mem, size, &mem) || mem > jas_max_mem) {
		jas_eprintf("STR");
		result = 0;
		mb = 0;
	} else {
		JAS_DBGLOG(100, ("STR", ext_size));
		if ((mb = malloc(ext_size))) {
			result = jas_mb_get_data(mb);
			mb->size = size;
			jas_mem = mem;
		} else {
			result = 0;
		}
	}
	JAS_DBGLOG(99, ("STR", size, result, mb));
	JAS_DBGLOG(102, ("STR", jas_max_mem, jas_mem));
	return result;
}