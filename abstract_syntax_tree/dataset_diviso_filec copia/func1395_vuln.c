regional_alloc(struct regional *r, size_t size)
{
	size_t a = ALIGN_UP(size, ALIGNMENT);
	void *s;
	
	if(a > REGIONAL_LARGE_OBJECT_SIZE) {
		s = malloc(ALIGNMENT + size);
		if(!s) return NULL;
		r->total_large += ALIGNMENT+size;
		*(char**)s = r->large_list;
		r->large_list = (char*)s;
		return (char*)s+ALIGNMENT;
	}
	
	if(a > r->available) {
		s = malloc(REGIONAL_CHUNK_SIZE);
		if(!s) return NULL;
		*(char**)s = r->next;
		r->next = (char*)s;
		r->data = (char*)s + ALIGNMENT;
		r->available = REGIONAL_CHUNK_SIZE - ALIGNMENT;
	}
	
	r->available -= a;
	s = r->data;
	r->data += a;
	return s;
}