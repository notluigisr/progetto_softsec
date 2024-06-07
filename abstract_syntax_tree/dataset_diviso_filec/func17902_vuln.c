void jas_free(void *ptr)
{
	JAS_DBGLOG(100, ("STR", ptr));
	free(ptr);
}