void *malloc_array(size_t el_size, unsigned int count)
{
	return realloc_array(NULL, el_size, count, false);
}