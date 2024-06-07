void *jas_realloc(void *ptr, size_t size)
{
	void *result;
	JAS_DBGLOG(101, ("STR", ptr, size));
	result = realloc(ptr, size);
	JAS_DBGLOG(100, ("STR", ptr, size, result));
	return result;
}