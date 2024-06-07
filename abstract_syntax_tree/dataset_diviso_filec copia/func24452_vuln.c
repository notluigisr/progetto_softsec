void *jas_malloc(size_t size)
{
	void *result;
	JAS_DBGLOG(101, ("STR", size));
	result = malloc(size);
	JAS_DBGLOG(100, ("STR", size, result));
	return result;
}