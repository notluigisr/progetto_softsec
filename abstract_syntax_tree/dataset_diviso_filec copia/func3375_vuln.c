regional_create_custom(size_t size)
{
	struct regional* r = (struct regional*)malloc(size);
	log_assert(sizeof(struct regional) <= size);
	if(!r) return NULL;
	r->first_size = size;
	regional_init(r);
	return r;
}