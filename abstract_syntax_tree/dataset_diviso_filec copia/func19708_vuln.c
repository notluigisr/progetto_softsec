static inline struct futex_hash_bucket *queue_lock(struct futex_q *q)
{
	struct futex_hash_bucket *hb;

	get_futex_key_refs(&q->key);
	hb = hash_futex(&q->key);
	q->lock_ptr = &hb->lock;

	spin_lock(&hb->lock);
	return hb;
}