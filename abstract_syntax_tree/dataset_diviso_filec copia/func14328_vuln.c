static struct audit_chunk *alloc_chunk(int count)
{
	struct audit_chunk *chunk;
	size_t size;
	int i;

	size = offsetof(struct audit_chunk, owners) + count * sizeof(struct node);
	chunk = kzalloc(size, GFP_KERNEL);
	if (!chunk)
		return NULL;

	INIT_LIST_HEAD(&chunk->hash);
	INIT_LIST_HEAD(&chunk->trees);
	chunk->count = count;
	for (i = 0; i < count; i++) {
		INIT_LIST_HEAD(&chunk->owners[i].list);
		chunk->owners[i].index = i;
	}
	inotify_init_watch(&chunk->watch);
	return chunk;
}