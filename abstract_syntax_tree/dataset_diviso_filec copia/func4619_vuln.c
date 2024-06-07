static inline void free_chunk(struct audit_chunk *chunk)
{
	call_rcu(&chunk->head, __free_chunk);
}